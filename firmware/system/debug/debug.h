/*
 * debug.h
 * 
 * Copyright (C) 2017-2019, Universidade Federal de Santa Catarina
 * 
 * This file is part of FloripaSat-Beacon.
 * 
 * FloripaSat-Beacon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-Beacon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-Beacon. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Functions for printing messages and bytes over UART port.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.10
 * 
 * \date 23/09/2016
 * 
 * \defgroup debug Debug
 * \ingroup system
 * \{
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * \brief Event types.
 */
typedef enum
{
    DEBUG_INFO,         /**< Information message. */
    DEBUG_WARNING,      /**< Warning message. */
    DEBUG_ERROR         /**< Error message. */
} debug_event_type_e;

/**
 * \brief Debug text colors list.
 */
typedef enum
{
    DEBUG_COLOR_BLACK = 0,      /**< Color black. */
    DEBUG_COLOR_RED,            /**< Color red. */
    DEBUG_COLOR_GREEN,          /**< Color green. */
    DEBUG_COLOR_YELLOW,         /**< Color yellow. */
    DEBUG_COLOR_BLUE,           /**< Color blue. */
    DEBUG_COLOR_MAGENTA,        /**< Color magenta. */
    DEBUG_COLOR_CYAN,           /**< Color cyan. */
    DEBUG_COLOR_WHITE           /**< Color white. */
} debug_colors_e;

/**
 * \brief Initialization of the debug mode.
 * 
 * \return TRUE/FALSE if successful or not:
 */
bool debug_init();

/**
 * \brief Sets the foreground color for the next debug message.
 *
 * This function uses the ANSI color code to output color debug messages.
 *
 * \param[in] color is the foreground color of text to select. It can be:
 * \parblock
 *      - DEBUG_COLOR_BLACK
 *      - DEBUG_COLOR_RED
 *      - DEBUG_COLOR_GREEN
 *      - DEBUG_COLOR_YELLOW
 *      - DEBUG_COLOR_BLUE
 *      - DEBUG_COLOR_MAGENTA
 *      - DEBUG_COLOR_CYAN
 *      - DEBUG_COLOR_WHITE
 *      .
 * \endparblock
 *
 * \return None.
 */
void debug_set_color(uint8_t color);

/**
 * \brief Resets the color back to normal.
 *
 * \return None.
 */
void debug_reset_color();

/**
 * \brief Prints a general event.
 *
 * \param[in] type is the type of event. It can be:
 * \parblock
 *      - DEBUG_INFO
 *      - DEBUG_WARNING
 *      - DEBUG_ERROR
 *      .
 * \endparblock
 * \param[in] event is the event text.
 *
 * \return None.
 */
void debug_print_event(uint8_t type, const char *event);

/**
 * \brief Prints an event from a system module.
 *
 * \param[in] type is the type of event. It can be:
 * \parblock
 *      - DEBUG_INFO
 *      - DEBUG_WARNING
 *      - DEBUG_ERROR
 *      .
 * \endparblock
 * \param[in] module is the module name.
 * \param[in] event is the event text.
 *
 * \return None.
 */
void debug_print_event_from_module(uint8_t type, const char *module, const char *event);

/**
 * \brief Prints a message over the UART.
 * 
 * \param msg is the message to be written.
 * 
 * \return None.
 */
void debug_print_msg(const char *msg);

/**
 * \brief Prints a integer digit over the debug UART.
 * 
 * \param d is the digit to be written (0 to 9)
 * 
 * \return None.
 */
void debug_print_digit(uint8_t d);

/**
 * \brief Prints a decimal number over the debug UART.
 *
 * \param[in] dec is the decimal number to print.
 *
 * \return None.
 */
void debug_print_dec(uint32_t dec);

/**
 * \brief Prints a hexadecimal value over the UART port.
 * 
 * Example:
 *      - Integer   = 0x65
 *      - Output    = "0x65"
 * 
 * \note The integer is printed in ASCII code.
 * 
 * \param hex is the hexadecimal to be written.
 * 
 * \return None.
 */
void debug_print_hex(uint32_t hex);

/**
 * \brief Prints a raw byte over the UART.
 * 
 * \param byte is the byte to be printed.
 * 
 * \return None.
 */
void debug_print_byte(uint8_t byte);

/**
 * \brief Prints the system time in milliseconds.
 *
 * \return None.
 */
void debug_print_system_time();

/**
 * \brief Prints the license text and genreal firmware information.
 *
 * \return None.
 */
void debug_print_license_msg();

/**
 * \brief Prints the splash screen of the firmware.
 *
 * \return None.
 */
void debug_print_splash_screen();

/**
 * \brief Writes the current firmware version.
 *
 * \return None.
 */
void debug_print_firmware_version();

/**
 * \brief Puts the program in an infinite loop.
 * 
 * This function can be used in case of a critical error during debug mode.
 * 
 * \return None.
 */
void debug_abort();

/**
 * \brief Initialization of the debug UART.
 * 
 * UART settings:
 *      - MCU interface = USCI_A1
 *      - Baudrate      = 115200 bps
 *      - Data bits     = 8
 *      - Parity bit    = None
 *      - Stop bits     = 1
 *      .
 * 
 * \return TRUE/FALSE if successful or not.
 */
bool debug_uart_init();

/**
 * \brief Writes a byte over the UART port.
 *
 * \param[in] byte is the byte to be written.
 *
 * \return None.
 */
void debug_uart_write_byte(uint8_t byte);

#endif // DEBUG_H_

//! \} End of debug group
