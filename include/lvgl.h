/**
 * @file lvgl.h
 * Include all LittleV GL related headers
 */

#ifndef LVGL_H
#define LVGL_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************
 * CURRENT VERSION OF LVGL
 ***************************/
#define LVGL_VERSION_MAJOR 7
#define LVGL_VERSION_MINOR 11
#define LVGL_VERSION_PATCH 0
#define LVGL_VERSION_INFO ""

/*********************
 *      INCLUDES
 *********************/

#include "lv_version.h"

#include "display/lv_misc/lv_log.h"
#include "display/lv_misc/lv_task.h"
#include "display/lv_misc/lv_math.h"
//#include "display/lv_misc/lv_async.h"
#include "display/lv_misc/lv_font.h"

#include "display/lv_hal/lv_hal.h"

#include "display/lv_core/lv_obj.h"
#include "display/lv_core/lv_group.h"
#include "display/lv_core/lv_indev.h"
#include "lv_core/lv_lang.h"
#include "lv_core/lv_vdb.h"
#include "display/lv_core/lv_refr.h"
//#include "display/lv_core/lv_disp.h"

#include "display/lv_themes/lv_theme.h"

#include "display/lv_fonts/lv_fonts.mk"
#include "display/lv_fonts/lv_font_builtin.h"

#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_imgbtn.h"
#include "display/lv_objx/lv_img.h"
#include "display/lv_objx/lv_label.h"
#include "display/lv_objx/lv_line.h"
#include "display/lv_objx/lv_page.h"
#include "display/lv_objx/lv_cont.h"
#include "display/lv_objx/lv_list.h"
#include "display/lv_objx/lv_chart.h"
#include "display/lv_objx/lv_table.h"
//#include "display/lv_objx/lv_checkbox.h"
//#include "display/lv_objx/lv_cpicker.h"
#include "display/lv_objx/lv_bar.h"
#include "display/lv_objx/lv_slider.h"
#include "display/lv_objx/lv_led.h"
//#include "display/lv_objx/lv_btnmatrix.h"
//#include "display/lv_objx/lv_keyboard.h"
//#include "display/lv_objx/lv_dropdown.h"
#include "display/lv_objx/lv_roller.h"
//#include "display/lv_objx/lv_textarea.h"
#include "display/lv_objx/lv_canvas.h"
#include "display/lv_objx/lv_win.h"
#include "display/lv_objx/lv_tabview.h"
#include "display/lv_objx/lv_tileview.h"
//#include "display/lv_objx/lv_msgbox.h"
//#include "display/lv_objx/lv_objmask.h"
#include "display/lv_objx/lv_gauge.h"
//#include "display/lv_objx/lv_linemeter.h"
//#include "display/lv_objx/lv_switch.h"
#include "display/lv_objx/lv_arc.h"
//#include "display/lv_objx/lv_spinner.h"
#include "display/lv_objx/lv_calendar.h"
#include "display/lv_objx/lv_spinbox.h"
#include "lv_objx/lv_cb.h"
#include "lv_objx/lv_btnm.h"
#include "lv_objx/lv_kb.h"
#include "lv_objx/lv_ddlist.h"
#include "lv_objx/lv_ta.h"
#include "lv_objx/lv_mbox.h"
#include "lv_objx/lv_lmeter.h"
#include "lv_objx/lv_sw.h"
#include "lv_objx/lv_kb.h"
#include "lv_objx/lv_preload.h"

#include "display/lv_draw/lv_draw_img.h"

//#include "display/lv_api_map.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

/** Gives 1 if the x.y.z version is supported in the current version
 * Usage:
 *
 * - Require v6
 * #if LV_VERSION_CHECK(6,0,0)
 *   new_func_in_v6();
 * #endif
 *
 *
 * - Require at least v5.3
 * #if LV_VERSION_CHECK(5,3,0)
 *   new_feature_from_v5_3();
 * #endif
 *
 *
 * - Require v5.3.2 bugfixes
 * #if LV_VERSION_CHECK(5,3,2)
 *   bugfix_in_v5_3_2();
 * #endif
 *
 * */
#define LV_VERSION_CHECK(x,y,z) (x == LVGL_VERSION_MAJOR && (y < LVGL_VERSION_MINOR || (y == LVGL_VERSION_MINOR && z <= LVGL_VERSION_PATCH)))

/**
 * Wrapper functions for VERSION macros
 */

static inline int lv_version_major(void)
{
    return LVGL_VERSION_MAJOR;
}

static inline int lv_version_minor(void)
{
    return LVGL_VERSION_MINOR;
}

static inline int lv_version_patch(void)
{
    return LVGL_VERSION_PATCH;
}

static inline const char *lv_version_info(void)
{
    return LVGL_VERSION_INFO;
}

#ifdef __cplusplus
}
#endif

#endif /*LVGL_H*/
