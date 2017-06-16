/*
 * main.c
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina.
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
 * \file main.c
 * 
 * \brief Main file.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 08/06/2017
 * 
 * \defgroup src Source
 * \{
 */

#include "beacon.h"

/**
 * \fn main
 * 
 * \brief The main function.
 * 
 * After the initializations of the peripherals, the program stays
 * running in a infinite loop. If the program get out of the main
 * infinite loop (If any critical error occurs), all the deinitialization
 * routines are excuted before the MCU turns off.
 * 
 * \return None
 */
void main()
{
    beacon_init();
    
    beacon_run();
    
    beacon_deinit();
    
    beacon_shutdown();
}

//! \} End of src group
