/**
 * \file liblvgl/llemu.hpp
 * \ingroup cpp-llemu
 * 
 * Legacy LCD Emulator
 *
 * \details This file defines a high-level API for emulating the three-button, UART-based
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
 * \defgroup cpp-llemu LLEMU C++ API
 * @{
 * LLEMU - Legacy Lcd EMUlator
 * \image html llemu/llemu-3.8.png
 * 
 * LLEMU provides a virtual 40x8 LCD screen with 3 buttons. The user can set the
 * text of the screen and set create functions that are run when the buttons are
 * pressed. 
 * 
 * LLEMU mimicks the behavior of the LCD devices for the cortex systems. 
 * @}
 */

#ifndef _LIBLVGL_LLEMU_HPP_
#define _LIBLVGL_LLEMU_HPP_

#include <cstdint>
#include <string>

#include "liblvgl/llemu.h"

/**
 * \ingroup cpp-llemu 
 */
namespace pros {
namespace lcd {

/**
 * \ingroup cpp-llemu 
 */

/**
 * \addtogroup cpp-llemu
 *  @{
 */

/**
 * \enum Text_Align
 * 
 * @brief Represents how to align the text in the LCD
 */
enum class Text_Align {
	/// Align the text to the left side of LCD
	LEFT = 0,
	/// Align the text to the center of the LCD
	CENTER = 1,
	/// Align the text to the right side of the LCD
	RIGHT = 2
};

/**
 * Checks whether the emulated three-button LCD has already been initialized.
 * 
 * \return True if the LCD has been initialized or false if not.
 * 
 * \b Example
 * \code
 * 	if (pros::lcd::is_initialized()) {
 * 		pros::lcd::print("LLEMU!");
 * 	}
 * 	else {
 * 		printf("Error: LLEMU is not initialized\n");
 * 	}
 * \endcode
 */
bool is_initialized(void);

/**
 * Creates an emulation of the three-button, UART-based VEX LCD on the display.
 *
 * \return True if the LCD was successfully initialized, or false if it has
 * already been initialized.
 * 
 * \b Example
 * \code
 *	#include "pros/llemu.hpp"
 * 
 *	void initialize() {
 * 		if (pros::lcd::initialize()) {
 * 			pros::lcd::print("LLEMU!");	
 * 		}
 * 		else {
 * 			printf("Error: LLEMU could not initailize\n");
 * 		}
 * 	}
 * \endcode
 */
bool initialize(void);

/**
 * Turns off the Legacy LCD Emulator.
 *
 * Calling this function will clear the entire display, and you will not be able
 * to call any further LLEMU functions until another call to lcd_initialize.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * ENXIO - The LCD has not been initialized. Call lcd_initialize() first.
 *
 * \return True if the operation was successful, or false otherwise, setting
 * errno values as specified above.
 * 
 * \b Example
 * \code
 * 	#include "pros/llemu.hpp"
 * 
 *	void disabled() {
		pros::lcd::shutdown();
 * 	}
 * \endcode
 */
bool shutdown(void);

/**
 * Displays a string on the emulated three-button LCD screen.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * ENXIO  - The LCD has not been initialized. Call lcd_initialize() first.
 * EINVAL - The line number specified is not in the range [0-7]
 *
 * \param line
 *        The line on which to display the text [0-7]
 * \param text
 *        The text to display
 *
 * \return True if the operation was successful, or false otherwise, setting
 * errno values as specified above.
 */
bool set_text(std::int16_t line, std::string text);

/**
 * Clears the contents of the emulated three-button LCD screen.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * ENXIO  - The LCD has not been initialized. Call lcd_initialize() first.
 * EINVAL - The line number specified is not in the range [0-7]
 *
 * \return True if the operation was successful, or false otherwise, setting
 * errno values as specified above.
 */
bool clear(void);

/**
 * Clears the contents of a line of the emulated three-button LCD screen.
 *
 * This function uses the following values of errno when an error state is
 * reached:
 * ENXIO  - The LCD has not been initialized. Call lcd_initialize() first.
 * EINVAL - The line number specified is not in the range [0-7]
 *
 * \param line
 *        The line to clear
 *
 * \return True if the operation was successful, or false otherwise, setting
 * errno values as specified above.
 */
bool clear_line(std::int16_t line);

using lcd_btn_cb_fn_t = void (*)(void);

/**
 * Registers a callback function for the leftmost button.
 *
 * When the leftmost button on the emulated three-button LCD is pressed, the
 * user-provided callback function will be invoked.
 *
 * \param cb
 * A callback function of type lcd_btn_cb_fn_t(void (*cb)(void))
 */
void register_btn0_cb(lcd_btn_cb_fn_t cb);

/**
 * Registers a callback function for the center button.
 *
 * When the center button on the emulated three-button LCD is pressed, the
 * user-provided callback function will be invoked.
 *
 * \param cb
 * A callback function of type lcd_btn_cb_fn_t(void (*cb)(void))
 */
void register_btn1_cb(lcd_btn_cb_fn_t cb);

/**
 * Registers a callback function for the rightmost button.
 *
 * When the rightmost button on the emulated three-button LCD is pressed, the
 * user-provided callback function will be invoked.
 *
 * \param cb
 * A callback function of type lcd_btn_cb_fn_t(void (*cb)(void))
 */
void register_btn2_cb(lcd_btn_cb_fn_t cb);

/**
 * Changes the alignment of text on the LCD background
 * 
 * \param alignment
 * 		An enum specifying the alignment. Available alignments are:
 * 			TEXT_ALIGN_LEFT
 * 			TEXT_ALIGN_RIGHT
 * 			TEXT_ALIGN_CENTER
 * 
 * \return void
 */
void set_text_align(Text_Align alignment);

/**
 * Gets the button status from the emulated three-button LCD.
 *
 * The value returned is a 3-bit integer where 1 0 0 indicates the left button
 * is pressed, 0 1 0 indicates the center button is pressed, and 0 0 1
 * indicates the right button is pressed. 0 is returned if no buttons are
 * currently being pressed.
 *
 * Note that this function is provided for legacy API compatibility purposes,
 * with the caveat that the V5 touch screen does not actually support pressing
 * multiple points on the screen at the same time.
 *
 * \return The buttons pressed as a bit mask
 */
std::uint8_t read_buttons(void);

///@}

}  // namespace lcd
}  // namespace pros


#endif  // _LIBLVGL_LLEMU_HPP_
