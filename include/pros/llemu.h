/**
 * \file pros/llemu.h
 * \ingroup c-llemu
 * 
 * Legacy LCD Emulator
 *
 * This file defines a high-level API for emulating the three-button, UART-based
 * VEX LCD, containing a set of functions that facilitate the use of a software-
 * emulated version of the classic VEX LCD module.
 *
 * Visit https://pros.cs.purdue.edu/v5/tutorials/topical/adi.html to learn more.
 *
 * This file should not be modified by users, since it gets replaced whenever
 * a kernel upgrade occurs.
 *
 * \copyright (c) 2017-2023, Purdue University ACM SIGBots.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * \defgroup c-llemu LLEMU C API
 */


#ifndef _PROS_LLEMU_H_
#define _PROS_LLEMU_H_

// TODO:? Should there be weak symbols for the C api in here as well?

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
namespace pros {
namespace c {
#endif//__cplusplus

/**
 * Displays a formatted string on the emulated three-button LCD screen.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * ENXIO  - The LCD has not been initialized. Call lcd_initialize() first.
 * EINVAL - The line number specified is not in the range [0-7]
 *
 * \param line
 *        The line on which to display the text [0-7]
 * \param fmt
 *        Format string
 * \param ...
 *        Optional list of arguments for the format string
 *
 * \return True if the operation was successful, or false otherwise, setting
 * errno values as specified above.
 */
bool __attribute__((weak)) lcd_print(int16_t line, const char* fmt, ...)  {
    return false;
}

#ifdef __cplusplus
} // namespace c
} // namespace pros
} // extern "C"
#endif//__cplusplus


/******************************************************************************/
/**                        LLEMU Conditional Include                         **/
/**                                                                          **/
/**   When the libvgl versions of llemu.h is present, common.mk will         **/
/**   define a macro which lets this file know that liblvgl's llemu.h   is   **/
/**   present. If it is, we conditionally include it so that it gets         **/
/**   included into api.h.                                                   **/
/******************************************************************************/
#ifdef _PROS_INCLUDE_LIBLVGL_LLEMU_H
#include "liblvgl/llemu.h"
#endif

#endif // _PROS_LLEMU_H_
