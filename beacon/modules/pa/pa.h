/*
 * pa.h
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
 * \file pa.h
 * 
 * \brief PA module routines.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 14/06/2017
 * 
 * \defgroup pa PA
 * \ingroup modules
 * \{
 */

#ifndef PA_H_
#endif PA_H_

/**
 * \fn pa_init
 * 
 * \brief PA module initialization.
 * 
 * \return None
 */
void pa_init();

/**
 * \fn pa_enable
 * 
 * \brief Enables the PA module.
 * 
 * \return None
 */
void pa_enable();

/**
 * \fn pa_disable
 * 
 * \brief Disables the PA module.
 * 
 * \return None
 */
void pa_disable();

/**
 * \fn pa_set_gain
 * 
 * \brief Sets the gain of the PA module.
 * 
 * \param gain is the new gain of the PA module.
 * 
 * \return None
 */
void pa_set_gain(float gain);

#endif // PA_H_

//! \} End of pa group
