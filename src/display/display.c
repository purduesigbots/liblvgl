/*
 * \file display/display.c
 *
 * Main source code for interacting with the V5 Brain's LCD screen.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "display/lvgl.h"
#include "api.h"

#include <assert.h>

static task_t disp_daemon_task;

static void disp_daemon(void* ign) {
	uint32_t time = millis();
	while (true) {
		printf("Daemon Loop:\n");
		printf("    lv_task_handler():\n");
		lv_task_handler();
		printf("    task_delay_until(%i, 2):\n", time);
		task_delay_until(&time, 2);
		printf("    lv_tick_inc(2)\n");
		lv_tick_inc(2);
	}
}

static void lvgl_display_flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color) {

	printf("Flush callback called!\n");
    if (screen_copy_area(area->x1, area->y1, area->x2, area->y2, (uint32_t*)color, area->x2 - area->x1 + 1) != 1) {
        errno = PROS_ERR;
		printf("Not Flusehd!");
    } else {
		printf("Flusehd!");
        lv_flush_ready();
    }
}

static void lvgl_read_touch(lv_indev_drv_t* _, lv_indev_data_t* data) {
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
}

void log_function(lv_log_level_t level, const char * file, uint32_t line,  const char * dsc) {
	char* log_level_string = "";
	switch(level) {
	case LV_LOG_LEVEL_TRACE: 
		log_level_string = "LVGL Trace";
		break;
	case LV_LOG_LEVEL_INFO : 
		log_level_string = "LVGL Info";
		break;
	case LV_LOG_LEVEL_WARN : 
		log_level_string = "LVGL Warning";
		break;
	case LV_LOG_LEVEL_ERROR: 
		log_level_string = "LVGL Error";
		break;
	default:
		log_level_string = "LVGL Unkown Log Level";
	}

	printf("%s (%s:%i): %s\n", log_level_string, file, line, dsc);
}

void display_initialize(void) {
	printf("Adding Print Callback\n");
	lv_log_register_print(log_function);

	printf("Initializing Display:\n");

	printf("    Initializing LVGL\n");
	lv_init();

	printf("    Initializing The Display Driver\n");
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.disp_flush = lvgl_display_flush;
	if(lv_disp_drv_register(&disp_drv) == NULL) {
		printf("    Could not add display driver!!!\n");
	}

	printf("    Initializing The Touch Driver\n");
	lv_indev_drv_t touch_drv;
	lv_indev_drv_init(&touch_drv);
	touch_drv.type = LV_INDEV_TYPE_POINTER;
	touch_drv.read = lvgl_read_touch;
	if(lv_indev_drv_register(&touch_drv) == NULL) {
		printf("    Could not add touch driver!!!\n");
	}

	lv_theme_set_current(lv_theme_alien_init(40, NULL));
	lv_obj_t* page = lv_obj_create(NULL, NULL);
	lv_obj_set_size(page, 480, 240);
	lv_scr_load(page);

	printf("    Initializing Display Daemon\n");
	disp_daemon_task = task_create(disp_daemon, NULL, TASK_PRIORITY_MIN + 2, TASK_STACK_DEPTH_DEFAULT,
	                                      "Display Daemon (PROS)");
}
