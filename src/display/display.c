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

static void vex_display_flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color/*int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t* color*/) {
	void vexDisplayCopyRect(int32_t, int32_t, int32_t, int32_t, uint32_t*, int32_t);

    // TODO: figure out if stride calculation is still correct
	vexDisplayCopyRect(area->x1, area->y1, area->x2, area->y2, (uint32_t*)color, area->x2 - area->x1 + 1);
	lv_disp_flush_ready(disp_drv);
}

static bool vex_read_touch(lv_indev_drv_t* _, lv_indev_data_t* data) {
	static struct {
		enum {
			kTouchEventRelease,
			kTouchEventPress,
			kTouchEventPressAuto,
		} lastEvent;
		int16_t lastXpos;
		int16_t lastYpos;
		int32_t pressCount;
		int32_t releaseCount;
	} v5_touch_status;

	bool vexTouchDataGet( typeof(v5_touch_status)* );
	vexTouchDataGet(&v5_touch_status);

	switch (v5_touch_status.lastEvent) {
		case kTouchEventPress:
		case kTouchEventPressAuto:
			data->state = LV_INDEV_STATE_PR;
			break;
		case kTouchEventRelease:
			data->state = LV_INDEV_STATE_REL;
			break;
	}
	// return last (x,y) pos in all cases https://doc.littlevgl.com/#Porting and
	// purduesigbots/pros#79
	data->point.x = v5_touch_status.lastXpos;
	data->point.y = v5_touch_status.lastYpos;
	return false;
}

static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf1[480 * 10];
static lv_color_t buf2[480 * 10];

static lv_disp_drv_t disp_drv;
static lv_indev_drv_t touch_drv;

void display_initialize(void) {
	lv_init();

    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, 480 * 10);

	lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = vex_display_flush;
    lv_disp_t* disp = lv_disp_drv_register(&disp_drv);

	lv_indev_drv_t touch_drv;
	lv_indev_drv_init(&touch_drv);
	touch_drv.type = LV_INDEV_TYPE_POINTER;
	touch_drv.read_cb = vex_read_touch;
	lv_indev_drv_register(&touch_drv);

	// lv_theme_set_current(lv_theme_alien_init(40, NULL));
	lv_obj_t* page = lv_obj_create(NULL);
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