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

#include "display/lvgl.h"
#include "api.h"
#include "pros/optical.h"
#include "pros/screen.h"
#include <errno.h>
#include <stdint.h>

static task_t disp_daemon_task;

static void disp_daemon(void* ign) {
	uint32_t time = millis();
	while (true) {
		lv_task_handler();
		task_delay_until(&time, 2);
		lv_tick_inc(2);
	}
}

static void lvgl_display_flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color) {
	if (screen_copy_area(area->x1, area->y1, area->x2, area->y2, (uint32_t*)color, area->x2 - area->x1 + 1) != 1) {
		errno = PROS_ERR;
	} else {
		lv_disp_flush_ready(disp_drv);
	}
}

static bool lvgl_read_touch(lv_indev_drv_t* _, lv_indev_data_t* data) {
	screen_touch_status_s_t status = screen_touch_status();

	switch (status.touch_status) {
		case E_TOUCH_PRESSED:
		case E_TOUCH_HELD:
			data->state = LV_INDEV_STATE_PR;
			break;
		case E_TOUCH_RELEASED:
			data->state = LV_INDEV_STATE_REL;
			break;
		case E_TOUCH_ERROR:
			errno = PROS_ERR;
			break;
	}
	// return last (x,y) pos in all cases https://doc.littlevgl.com/#Porting and
	// purduesigbots/pros#79
	data->point.x = status.x;
	data->point.y = status.y;
	return false;
}

static lv_disp_buf_t disp_buf;
static lv_color_t buf1[480 * 10];
static lv_color_t buf2[480 * 10];

static lv_disp_drv_t disp_drv;
static lv_indev_drv_t touch_drv;

void display_initialize(void) {
	lv_init();

    lv_disp_buf_init(&disp_buf, buf1, buf2, 480 * 10);

	lv_disp_drv_init(&disp_drv);
    disp_drv.buffer = &disp_buf;
	disp_drv.flush_cb = lvgl_display_flush;
    lv_disp_t* disp = lv_disp_drv_register(&disp_drv);

	lv_indev_drv_t touch_drv;
	lv_indev_drv_init(&touch_drv);
	touch_drv.type = LV_INDEV_TYPE_POINTER;
	touch_drv.read_cb = lvgl_read_touch;
	lv_indev_drv_register(&touch_drv);

	// lv_theme_set_current(lv_theme_alien_init(40, NULL));
	lv_obj_t* page = lv_obj_create(NULL, NULL);
	lv_obj_set_size(page, 480, 240);
	lv_scr_load(page);

	disp_daemon_task = task_create(
		disp_daemon,
		NULL,
		TASK_PRIORITY_MIN + 2,
		TASK_STACK_DEPTH_DEFAULT,
		"Display Daemon (PROS)"
	);
}