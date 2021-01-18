/*
 * debug.c
 * 
 * Copyright (C) 2017-2019, Universidade Federal de Santa Catarina
 * 
 * This file is part of FloripaSat-TTC.
 * 
 * FloripaSat-TTC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-TTC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-TTC. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Debug functions implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.0
 * 
 * \date 23/09/2016
 * 
 * \addtogroup debug
 * \{
 */

#include <math.h>

#include <system/time/time.h>
#include <version.h>

#include "debug.h"
#include "debug_config.h"

bool debug_init()
{
#if BEACON_DEBUG_MESSAGES == 1
    if (debug_uart_init())
    {
        debug_print_msg("\n\r");

        debug_print_license_msg();

        debug_print_splash_screen();

        debug_print_msg("=================================================================\n\r");
        debug_print_msg("Version:\t");
        debug_print_firmware_version();
        debug_print_msg("\n\r");

        debug_print_msg("Status:\t\t");
        debug_print_msg(FIRMWARE_STATUS);
        debug_print_msg("\n\r");

        debug_print_msg("Author:\t\t");
        debug_print_msg(FIRMWARE_AUTHOR_NAME);
        debug_print_msg(" <");
        debug_print_msg(FIRMWARE_AUTHOR_EMAIL);
        debug_print_msg(">\n\r");
        debug_print_msg("=================================================================\n\r");
        debug_print_msg("\n\n\r");

        return true;
    }
    else
    {
        return false;
    }
#else
    return true;
#endif // BEACON_DEBUG_MESSAGES
}

void debug_set_color(uint8_t color)
{
    switch(color)
    {
        case DEBUG_COLOR_BLACK:
            debug_print_msg("\033[1;30m");
            break;
        case DEBUG_COLOR_RED:
            debug_print_msg("\033[1;31m");
            break;
        case DEBUG_COLOR_GREEN:
            debug_print_msg("\033[1;32m");
            break;
        case DEBUG_COLOR_YELLOW:
            debug_print_msg("\033[1;33m");
            break;
        case DEBUG_COLOR_BLUE:
            debug_print_msg("\033[1;34m");
            break;
        case DEBUG_COLOR_MAGENTA:
            debug_print_msg("\033[1;35m");
            break;
        case DEBUG_COLOR_CYAN:
            debug_print_msg("\033[1;36m");
            break;
        case DEBUG_COLOR_WHITE:
            debug_print_msg("\033[1;37m");
            break;
        default:
            debug_reset_color();
    }
}

void debug_reset_color()
{
    debug_print_msg("\033[0m");
}

void debug_print_event(uint8_t type, const char *event)
{
    debug_print_system_time();
    debug_print_msg(" ");

    switch(type)
    {
        case DEBUG_INFO:
            break;
        case DEBUG_WARNING:
            debug_set_color(DEBUG_WARNING_COLOR);
            break;
        case DEBUG_ERROR:
            debug_set_color(DEBUG_ERROR_COLOR);
            break;
        default:
            break;
    }

    debug_print_msg(event);
}

void debug_print_event_from_module(uint8_t type, const char *module, const char *event)
{
    debug_print_system_time();

    debug_set_color(DEBUG_MODULE_NAME_COLOR);
    debug_print_msg(" ");
    debug_print_msg(module);
    debug_reset_color();
    debug_print_msg(": ");

    switch(type)
    {
        case DEBUG_INFO:
            break;
        case DEBUG_WARNING:
            debug_set_color(DEBUG_WARNING_COLOR);
            break;
        case DEBUG_ERROR:
            debug_set_color(DEBUG_ERROR_COLOR);
            break;
        default:
            break;
    }

    debug_print_msg(event);
}

void debug_print_msg(const char *msg)
{
    uint8_t i = 0;
    while(msg[i] != '\0')
    {
        if (msg[i] == '\n')
        {
            debug_reset_color();
        }

        debug_print_byte(msg[i]);
        i++;
    }
}

void debug_print_digit(uint8_t digit)
{
    if (digit < 0x0A)
    {
        debug_print_byte(digit + 0x30);    // 0x30 = ascii 0
    }
    else if (digit <= 0x0F)
    {
        debug_print_byte(digit + 0x37);    // 0x37 = ascii 7
    }
    else
    {
        debug_print_byte('N');
    }
}

void debug_print_dec(uint32_t dec)
{
    if (dec == 0)
    {
        debug_print_digit(0);
    }
    else
    {
        uint8_t dec_str[10];                        // 32-bits = decimal with 10 digits

        uint8_t digits = log10(dec) + 1;

        uint8_t i = 0;
        for(i=0; i<digits; ++i, dec /= 10)
        {
            dec_str[i] = dec % 10;
        }

        uint8_t j = 0;
        for(j=i; j>0; j--)
        {
            debug_print_digit(dec_str[j-1]);
        }
    }
}

void debug_print_hex(uint32_t hex)
{
    debug_print_msg("0x");
    
    if (hex > 0x00FFFFFF)
    {
        debug_print_digit((uint8_t)(hex >> 28) & 0x0F);
        debug_print_digit((uint8_t)(hex >> 24) & 0x0F);
    }

    if (hex > 0x0000FFFF)
    {
        debug_print_digit((uint8_t)(hex >> 20) & 0x0F);
        debug_print_digit((uint8_t)(hex >> 16) & 0x0F);
    }

    if (hex > 0x000000FF)
    {
        debug_print_digit((uint8_t)(hex >> 12) & 0x0F);
        debug_print_digit((uint8_t)(hex >> 8) & 0x0F);
    }

    debug_print_digit((uint8_t)(hex >> 4) & 0x0F);
    debug_print_digit((uint8_t)(hex & 0x0F));
}

void debug_print_byte(uint8_t byte)
{
#if BEACON_DEBUG_MESSAGES == 1
    debug_uart_write_byte(byte);
#endif // BEACON_DEBUG_MESSAGES
}

void debug_print_system_time()
{
    debug_set_color(DEBUG_SYSTEM_TIME_COLOR);

    debug_print_msg("[ ");
    debug_print_dec(time_get_seconds());
    debug_print_msg(" ]");

    debug_reset_color();
}

void debug_print_license_msg()
{
    debug_print_msg("FloripaSat-Beacon Copyright (C) 2017-2019, Universidade Federal de Santa Catarina;\n\r");
    debug_print_msg("This program comes with ABSOLUTELY NO WARRANTY.\n\r");
    debug_print_msg("This is free software, and you are welcome to redistribute it\n\r");
    debug_print_msg("under certain conditions.\n\n\r");
    debug_print_msg("Source code: https://github.com/floripasat/ttc\n\r");
    debug_print_msg("Documentation: https://github.com/floripasat/ttc/wiki\n\r");
}

void debug_print_splash_screen()
{
    debug_print_msg("                                                                 \n\r");
    debug_print_msg("                                                                 \n\r");
    debug_print_msg(".................................................................\n\r");
    debug_print_msg(".................................................................\n\r");
    debug_print_msg("..........                                             ..........\n\r");
    debug_print_msg("..........  _____ ____        _      _____ _____ ____  ..........\n\r");
    debug_print_msg(".......... |  ___/ ___|  __ _| |_   |_   _|_   _/ ___| ..........\n\r");
    debug_print_msg(".......... | |_  \\___ \\ / _` | __|____| |   | || |     ..........\n\r");
    debug_print_msg(".......... |  _|  ___) | (_| | ||_____| |   | || |___  ..........\n\r");
    debug_print_msg(".......... |_|   |____/ \\__,_|\\__|    |_|   |_| \\____| ..........\n\r");
    debug_print_msg("..........                                             ..........\n\r");
    debug_print_msg(".................................................................\n\r");
    debug_print_msg(".................................................................\n\r");
    debug_print_msg("                                                                 \n\r");
    debug_print_msg("                                                                 \n\r");
}

void debug_print_firmware_version()
{
    debug_print_msg("[ ");
    debug_print_msg(FIRMWARE_VERSION);
    debug_print_msg(" ]");
}

void debug_abort()
{
#if BEACON_DEBUG_MESSAGES == 1
    while(1)
    {
        
    }
#endif // BEACON_DEBUG_MESSAGES
}

//! \} End of debug group
