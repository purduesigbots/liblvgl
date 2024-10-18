/*
 * \file display/display.c
 *
 * Main source code for interacting with the V5 Brain's LCD screen.
 *
 * Copyright (c) 2017-2020, Purdue University ACM SIGBots.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "liblvgl/lvgl.h"
#include "api.h"
#include "pros/optical.h"
#include "pros/screen.h"
#include <errno.h>
#include <stdint.h>
#include <assert.h>

#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_ARGB8888)) /*will be 2 for RGB565 */
#define PROS_LVGL_DISPLAY_BUGGER_SIZE (LV_HOR_RES_MAX * 10 * BYTES_PER_PIXEL)


static void disp_daemon(void* ign) {
	uint32_t time = millis();

	while (true) {
		task_delay_until(&time, 2);
		lv_tick_inc(2);
		lv_timer_handler();
	}
}

static void lvgl_display_flush(lv_display_t* display, const lv_area_t* area, uint8_t* color) {
	if (screen_copy_area(area->x1, area->y1, area->x2, area->y2, (uint32_t*)color, area->x2 - area->x1 + 1) != 1) {
		errno = PROS_ERR;
	} else {
		lv_display_flush_ready(display);
	}
}

static void lvgl_read_touch(lv_indev_t* _, lv_indev_data_t* data) {
	screen_touch_status_s_t status = screen_touch_status();

	switch (status.touch_status) {
		case E_TOUCH_PRESSED:
		case E_TOUCH_HELD:
			data->state = LV_INDEV_STATE_PRESSED;
			break;
		case E_TOUCH_RELEASED:
			data->state = LV_INDEV_STATE_RELEASED;
			break;
		case E_TOUCH_ERROR:
			errno = PROS_ERR;
			break;
	}

	// return last (x,y) pos in all cases https://doc.littlevgl.com/#Porting and
	// purduesigbots/pros#79
	data->point.x = status.x;
	data->point.y = status.y;
}

static task_t disp_daemon_task;

LV_ATTRIBUTE_MEM_ALIGN
static lv_color_t display_buffer_1[PROS_LVGL_DISPLAY_BUGGER_SIZE];
LV_ATTRIBUTE_MEM_ALIGN
static lv_color_t display_buffer_2[PROS_LVGL_DISPLAY_BUGGER_SIZE];

static lv_display_t * display_device;
static lv_indev_t * touch_device;

/*
So this is what this function is supposed to do, and why it's important.

Everything is pulled from here: 
https://docs.lvgl.io/8.3/porting/index.html

TLDR, this is what it is supposed to do:
1. Call lv_init().

2. Initialize your drivers.

3. Register the display and input devices drivers in LVGL. 
More about Display and Input device registration.

4. Call lv_tick_inc(x) in every x milliseconds in an interrupt 
to tell the elapsed time. Learn more.

5. Call lv_task_handler() periodically in every few milliseconds 
to handle LVGL related tasks. This is *supposed* to be done with 
disp_daemon_task and it does, but it's not working as the flush_cb,
touch_cb, and other callbacks aren't triggering after boot-up. 
*/

void display_initialize(void) {
	lv_init();

	// register display

	// create a display
	display_device = lv_display_create(LV_HOR_RES_MAX, LV_VER_RES_MAX);
	// configure buffers
	// partial render mode will render only diffs and not static backgrounds, e.g.
	lv_display_set_buffers(
		display_device,
		display_buffer_1,
		display_buffer_2,
		sizeof(display_buffer_1),
		LV_DISPLAY_RENDER_MODE_PARTIAL);
	
	// the "flush callback" is what copies pixels from buffer to screen
	lv_display_set_flush_cb(display_device, lvgl_display_flush);

	// register input

	// create input

	// internally the function uses the default display, which doesn't exist until the
	// first display is created, which then becomes the default.
	touch_device = lv_indev_create();
	lv_indev_set_type(touch_device, LV_INDEV_TYPE_POINTER);
	lv_indev_set_read_cb(touch_device, lvgl_read_touch);


	lv_obj_t* page = lv_obj_create(NULL);
	lv_obj_set_size(page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_screen_load(page);

	disp_daemon_task = task_create(
		disp_daemon,
		NULL,
		TASK_PRIORITY_MIN + 2,
		TASK_STACK_DEPTH_DEFAULT,
		"Display Daemon (PROS)"
	);
} 