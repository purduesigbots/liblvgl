/*
 * \file display/llemu.c
 *
 * Legacy LCD Emulator
 *
 * This file defines a high-level API for emulating the three-button, UART-based
 * VEX LCD, containing a set of functions that facilitate the use of a software-
 * emulated version of the classic VEX LCD module.
 *
 * Copyright (c) 2017-2020, Purdue University ACM SIGBots.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "core/lv_disp.h"
#include "core/lv_obj.h"
#include "core/lv_obj_style.h"
#include "font/lv_font.h"
#include "misc/lv_color.h"
#include "widgets/lv_btn.h"
#define _GNU_SOURCE
// NOTE: this would normally be in the C file, but it won't compile that way
#include <stdio.h>  // vasprintf (GNU extension)
#undef _GNU_SOURCE
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "pros/llemu.h"



static lv_style_t frame_style;
static lv_style_t screen_style;
static lv_style_t button_style;
static lv_style_t button_pressed_style;

static void touch_bits_update_pressed(lv_obj_t* btn) {
	lcd_s_t* lcd = lv_obj_get_parent(lv_obj_get_parent(lv_obj_get_parent(btn)))->user_data;

	if (btn == lcd->btns[0])
		lcd->touch_bits |= (1 << 2);
	else if (btn == lcd->btns[1])
		lcd->touch_bits |= (1 << 1);
	else if (btn == lcd->btns[2])
		lcd->touch_bits |= (1 << 0);
}

void touch_bits_update_released(lcd_s_t* lcd, size_t btn) {
	lcd->touch_bits &= ~(1 << btn);
}

static void button_event_handler(lv_obj_t* btn, lv_event_code_t event) {
	lcd_s_t* lcd = lv_obj_get_parent(lv_obj_get_parent(lv_obj_get_parent(btn)))->user_data;
    switch (event) {
        case LV_EVENT_PRESSED:
            touch_bits_update_pressed(btn);
            break;

        case LV_EVENT_CLICKED:
            if (btn == lcd->btns[0]) {
                if (lcd->callbacks[0]) (lcd->callbacks[0])();
                touch_bits_update_released(lcd, 2);
            } else if (btn == lcd->btns[1]) {
                if (lcd->callbacks[1]) (lcd->callbacks[1])();
                touch_bits_update_released(lcd, 1);
            } else if (btn == lcd->btns[2]) {
                if (lcd->callbacks[2]) (lcd->callbacks[2])();
                touch_bits_update_released(lcd, 0);
            }
            break;
    }
}

static lv_obj_t* _create_lcd(void) {
    static lv_style_t lv_style_transp_fit;

	lv_obj_t* lcd_dummy = lv_obj_create(lv_scr_act());
	lv_obj_set_size(lcd_dummy, LV_HOR_RES, LV_VER_RES);

	lv_obj_t* frame = lv_obj_create(lcd_dummy);
	lv_obj_set_size(frame, LV_HOR_RES, LV_VER_RES);
	lv_obj_add_style(frame, &frame_style, LV_STATE_DEFAULT);
	lv_obj_set_flex_flow(frame, LV_FLEX_FLOW_COLUMN);

	lv_obj_t* screen = lv_obj_create(frame);
	lv_obj_set_size(screen, 426, 160);
	lv_obj_align(screen, LV_ALIGN_TOP_MID, 0, 19);
	lv_obj_add_style(screen, &screen_style, LV_PART_MAIN);

	lv_obj_t* btn_container = lv_obj_create(frame);
	lv_obj_set_size(btn_container, 426, 30);
	lv_obj_align(btn_container, LV_ALIGN_BOTTOM_MID, 0, -20);
	lv_obj_add_style(btn_container, &lv_style_transp_fit, LV_PART_MAIN);
	lv_obj_set_style_border_width(btn_container, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_pad_all(btn_container, LV_STATE_DEFAULT, 0);
	lv_obj_set_flex_flow(btn_container, LV_FLEX_FLOW_ROW);

	lv_obj_t* btn_left = lv_btn_create(btn_container);
	lv_obj_set_width(btn_left, 80);
	lv_obj_align(btn_left, LV_ALIGN_LEFT_MID, 0, 0);
	lv_obj_add_style(btn_left, &button_style, LV_PART_MAIN);
    //lv_obj_set_event_cb(btn_left, button_event_handler);

	lv_obj_t* btn_center = lv_btn_create(btn_container);
	lv_obj_set_width(btn_center, 80);
	lv_obj_align(btn_center, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(btn_center, &button_style, LV_PART_MAIN);
    //lv_obj_set_event_cb(btn_center, button_event_handler);

	lv_obj_t* btn_right = lv_btn_create(btn_container);
	lv_obj_set_width(btn_right, 80);
	lv_obj_align(btn_right, LV_ALIGN_RIGHT_MID, 0, 0);
	lv_obj_add_style(btn_right, &button_style, LV_PART_MAIN);
	//lv_obj_set_event_cb(btn_right, button_event_handler);

	lv_obj_set_style_bg_color(frame, lv_color_hex(0x808080), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(frame, lv_color_hex(0xC0C0C0), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(frame, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

    lv_obj_set_style_bg_color(screen, lv_color_hex(0x5ABC03), LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(screen, lv_color_hex(0x323D13), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(screen, &lv_font_unscii_16, LV_STATE_DEFAULT); // TODO: does this need to be 20px?

    lv_obj_set_style_bg_color(btn_left, lv_color_hex(0x808080),  LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(btn_left, lv_color_hex(0x303030), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btn_left, lv_color_hex(0x0A0A0A), LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_color(btn_left, lv_color_hex(0x808080), LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(btn_left, LV_STATE_DEFAULT | LV_STATE_PRESSED, LV_GRAD_DIR_VER);

	lv_obj_set_style_bg_color(btn_right, lv_color_hex(0x808080),  LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(btn_right, lv_color_hex(0x303030), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btn_right, lv_color_hex(0x0A0A0A), LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_color(btn_right, lv_color_hex(0x808080), LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(btn_right, LV_STATE_DEFAULT | LV_STATE_PRESSED, LV_GRAD_DIR_VER);

	lv_obj_set_style_bg_color(btn_center, lv_color_hex(0x808080),  LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(btn_center, lv_color_hex(0x303030), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btn_center, lv_color_hex(0x0A0A0A), LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_color(btn_center, lv_color_hex(0x808080), LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(btn_center, LV_STATE_DEFAULT | LV_STATE_PRESSED, LV_GRAD_DIR_VER);

	lcd_s_t* lcd = (lcd_s_t*)malloc(sizeof(lcd_s_t));
	lcd_dummy->user_data = lcd;
	lcd->frame = frame;
	lcd->screen = screen;

	lcd->btn_container = btn_container;
	lcd->btns[0] = btn_left;
	lcd->btns[1] = btn_center;
	lcd->btns[2] = btn_right;
	lcd->callbacks[0] = NULL;
	lcd->callbacks[1] = NULL;
	lcd->callbacks[2] = NULL;

	for (size_t i = 0; i < 8; i++) {
		lcd->lcd_text[i] = lv_label_create(lcd->screen);
		lv_obj_set_width(lcd->lcd_text[i], 426);
		lv_obj_align(lcd->lcd_text[i], LV_ALIGN_TOP_LEFT, 5, 20 * i);
		// lv_label_set_align(lcd->lcd_text[i], LV_TEXT_ALIGN_LEFT);
		lv_label_set_long_mode(lcd->lcd_text[i], LV_LABEL_LONG_CLIP);
		// lv_label_set_no_break(lcd->lcd_text[i], true); 
		lv_label_set_text(lcd->lcd_text[i], "");
	}

	return lcd_dummy;
}

bool _lcd_vprint(lv_obj_t* lcd_dummy, int16_t line, const char* fmt, va_list args) {
	if (line < 0 || line > 7) {
		errno = EINVAL;
		return false;
	}
	lcd_s_t* lcd = lcd_dummy->user_data;
	char buf[33];
	vsnprintf(buf, 33, fmt, args);

	lv_label_set_text(lcd->lcd_text[line], buf);
	lv_obj_set_width(lcd->lcd_text[line], 426);
	return true;
}

bool _lcd_print(lv_obj_t* lcd_dummy, int16_t line, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	bool res = _lcd_vprint(lcd_dummy, line, fmt, args);
	va_end(args);
	return res;
}

bool _lcd_set_text(lv_obj_t* lcd_dummy, int16_t line, const char* text) {
	return _lcd_print(lcd_dummy, line, "%s", text);
}

void _lcd_clear(lv_obj_t* lcd_dummy) {
	lcd_s_t* lcd = lcd_dummy->user_data;
	// delete children of screen (this is fine because when we print, we just
	// overwrite the pointer anyway)
	lv_obj_clean(lcd->screen);
}

bool _lcd_clear_line(lv_obj_t* lcd_dummy, int16_t line) {
	if (line < 0 || line > 7) {
		errno = EINVAL;
		return false;
	}
	lcd_s_t* lcd = lcd_dummy->user_data;
	lv_label_set_text(lcd->lcd_text[line], "");
	return true;
}

void _lcd_set_left_callback(lv_obj_t* lcd_dummy, lcd_btn_cb_fn_t cb) {
	lcd_s_t* lcd = lcd_dummy->user_data;
	lcd->callbacks[0] = cb;
}
void _lcd_set_center_callback(lv_obj_t* lcd_dummy, lcd_btn_cb_fn_t cb) {
	lcd_s_t* lcd = lcd_dummy->user_data;
	lcd->callbacks[1] = cb;
}
void _lcd_set_right_callback(lv_obj_t* lcd_dummy, lcd_btn_cb_fn_t cb) {
	lcd_s_t* lcd = lcd_dummy->user_data;
	lcd->callbacks[2] = cb;
}

uint8_t _lcd_read_buttons(lv_obj_t* lcd_dummy) {
	lcd_s_t* lcd = lcd_dummy->user_data;
	return lcd->touch_bits;
}

static volatile bool _lcd_is_initialized = false;
bool lcd_is_initialized(void) {
	return _lcd_is_initialized;
}

static lv_obj_t* _llemu_lcd;
bool lcd_initialize(void) {
	if (lcd_is_initialized()) return false;

	_llemu_lcd = _create_lcd();
	if (!_llemu_lcd) return false;

	_lcd_is_initialized = true;
	return true;
}

bool lcd_shutdown(void) {
	if (!lcd_is_initialized()) {
		errno = ENXIO;
		return false;
	}
	lv_obj_del(_llemu_lcd);
	_lcd_is_initialized = false;
	return true;
}

bool lcd_print(int16_t line, const char* fmt, ...) {
	if (!lcd_is_initialized()) {
		errno = ENXIO;
		return false;
	}
	va_list args;
	va_start(args, fmt);
	bool res = _lcd_vprint(_llemu_lcd, line, fmt, args);
	va_end(args);
	return res;
}

bool lcd_set_text(int16_t line, const char* text) {
	if (!lcd_is_initialized()) {
		errno = ENXIO;
		return false;
	}
	return _lcd_set_text(_llemu_lcd, line, text);
}

bool lcd_clear(void) {
	if (!lcd_is_initialized()) {
		errno = ENXIO;
		return false;
	}
	_lcd_clear(_llemu_lcd);
	return true;
}

bool lcd_clear_line(int16_t line) {
	if (!lcd_is_initialized()) {
		errno = ENXIO;
		return false;
	}
	return _lcd_clear_line(_llemu_lcd, line);
}

bool lcd_register_btn0_cb(lcd_btn_cb_fn_t cb) {
	if (!lcd_is_initialized()) {
		errno = ENXIO;
		return false;
	}
	_lcd_set_left_callback(_llemu_lcd, cb);
	return true;
}

bool lcd_register_btn1_cb(lcd_btn_cb_fn_t cb) {
	if (!lcd_is_initialized()) {
		errno = ENXIO;
		return false;
	}
	_lcd_set_center_callback(_llemu_lcd, cb);
	return true;
}

bool lcd_register_btn2_cb(lcd_btn_cb_fn_t cb) {
	if (!lcd_is_initialized()) {
		errno = ENXIO;
		return false;
	}
	_lcd_set_right_callback(_llemu_lcd, cb);
	return true;
}

uint8_t lcd_read_buttons(void) {
	if (!lcd_is_initialized()) {
		errno = ENXIO;
		return 0;
	}
	return _lcd_read_buttons(_llemu_lcd);
}
