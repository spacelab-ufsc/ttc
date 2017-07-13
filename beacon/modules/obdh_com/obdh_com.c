/*
 * obdh_com.c
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina
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
 * \file obdh_com.c
 * 
 * \brief Implementation of the functions to communicate with the OBDH module.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/03/2017
 * 
 * \addtogroup obdh_com
 * \{
 */

#include <stdbool.h>
#include <string.h>

#include <config/config.h>
#include <modules/modules.h>
#include <libs/driverlib/driverlib.h>
#include <libs/crc/crc.h>
#include <src/tasks.h>
#include <src/beacon.h>

#include "obdh_com.h"

OBDH *obdh_ptr;

uint8_t obdh_com_init(OBDH *obdh)
{
#if BEACON_MODE == DEBUG_MODE
    debug_print_msg("OBDH communication initialization... ");
#endif // BEACON_MODE
    
    obdh_ptr = obdh;
    
    // obdh_com initialization
    obdh->received_byte = 0x00;
    obdh->byte_counter  = 0;
    obdh->crc_fails     = 0;
    obdh->is_open       = false;
    
    obdh_com_clear_buffer(obdh->buffer);
    
    // obdh_data initialization
    obdh_com_save_data_from_buffer(obdh->buffer, &obdh->data);
    
    if (obdh_com_spi_init() == STATUS_FAIL)
    {
        obdh->is_open = false;
        
#if BEACON_MODE == DEBUG_MODE
        debug_print_msg("FAIL!\n");
#endif // BEACON_MODE

        return STATUS_FAIL;
    }
    else
    {
        obdh->is_open = true;
        
#if BEACON_MODE == DEBUG_MODE
        debug_print_msg("SUCCESS!\n");
#endif // BEACON_MODE

        return STATUS_SUCCESS;
    }
}

static uint8_t obdh_com_spi_init()
{
    // If clock signal from master stays low, it is not yet in SPI mode
    while(GPIO_getInputPinValue(OBDH_COM_SPI_PORT, OBDH_COM_SPI_SCLK_PIN) == GPIO_INPUT_PIN_LOW)
    {
        
    }
    
    // SPI pins init.
    GPIO_setAsPeripheralModuleFunctionInputPin(OBDH_COM_SPI_PORT, OBDH_COM_SPI_MOSI_PIN + OBDH_COM_SPI_MISO_PIN + OBDH_COM_SPI_SCLK_PIN);
    
    if (USCI_A_SPI_initSlave(OBDH_COM_SPI_BASE_ADDRESS, USCI_A_SPI_MSB_FIRST,
                             USCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
                             USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW) == STATUS_SUCCESS)
    {
        // Enable SPI Module
        USCI_A_SPI_enable(OBDH_COM_SPI_BASE_ADDRESS);

        // Enable Receive interrupt
        USCI_A_SPI_clearInterrupt(OBDH_COM_SPI_BASE_ADDRESS, USCI_A_SPI_RECEIVE_INTERRUPT);
        USCI_A_SPI_enableInterrupt(OBDH_COM_SPI_BASE_ADDRESS, USCI_A_SPI_RECEIVE_INTERRUPT);
        
        return STATUS_SUCCESS;
    }
    else
    {
        return STATUS_FAIL;
    }
}

static void obdh_com_receive_data(OBDH *obdh)
{
#if BEACON_MODE == DEBUG_MODE
        debug_print_msg("Receiving a byte from the OBDH module... ");
#endif // DEBUG_MODE

    obdh->received_byte = USCI_A_SPI_receiveData(OBDH_COM_SPI_BASE_ADDRESS);
    
    switch(obdh->byte_counter)
    {
        case OBDH_COM_CMD_POSITION:
            obdh_com_receive_cmd(obdh, obdh->received_byte);
            break;
        case OBDH_COM_SOD_POSITION:
            if (obdh->received_byte == OBDH_COM_START_OF_DATA)
            {
#if BEACON_MODE == DEBUG_MODE
                debug_print_msg("SOD byte received!\n");
#endif // DEBUG_MODE
                obdh->byte_counter++;
            }
            else
            {
#if BEACON_MODE == DEBUG_MODE
                debug_print_msg("ERROR! Invalid SOD byte received!\nWaiting a new valid command...\n");
#endif // DEBUG_MODE
                obdh->byte_counter = OBDH_COM_CMD_POSITION;
            }
            break;
        case OBDH_COM_CRC_POSITION:
#if BEACON_MODE == DEBUG_MODE
            debug_print_msg("Checking CRC... ");
#endif // DEBUG_MODE
            if (obdh->received_byte == crc8(OBDH_COM_CRC_INITIAL_VALUE, OBDH_COM_CRC_POLYNOMIAL, obdh->buffer, OBDH_COM_DATA_PKT_LEN))
            {
#if BEACON_MODE == DEBUG_MODE
                debug_print_msg("VALID!\n");
#endif // DEBUG_MODE
                obdh_com_save_data_from_buffer(obdh->buffer, &obdh->data);
                obdh->crc_fails = 0;
            }
            else
            {
#if BEACON_MODE == DEBUG_MODE
                debug_print_msg("ERROR! INVALID!\n");
#endif // DEBUG_MODE
                obdh_com_clear_buffer(obdh->buffer);
                obdh->crc_fails++;
            }
            break;
        default:
            if ((obdh->byte_counter > OBDH_COM_SOD_POSITION) && (obdh->byte_counter < OBDH_COM_CRC_POSITION))
            {
                obdh_com_receive_pkt(obdh, obdh->received_byte);
            }
            else
            {
                obdh->byte_counter = OBDH_COM_CMD_POSITION;
            }
            break;
    }
}

static void obdh_com_receive_cmd(OBDH *obdh, uint8_t cmd)
{
    switch(cmd)
    {
        case OBDH_COM_CMD_START_OF_DATA_TRANSFER:
#if BEACON_MODE == DEBUG_MODE
            debug_print_msg("Data transfer command received!\n");
#endif // DEBUG_MODE
            obdh->byte_counter = OBDH_COM_SOD_POSITION;
            break;
        case OBDH_COM_CMD_SHUTDOWN_REQUEST:
#if BEACON_MODE == DEBUG_MODE
            debug_print_msg("Shutdown command received!\n");
#endif // DEBUG_MODE
            obdh_com_send_data(OBDH_COM_SHUTDOWN_ACK);
            task_enter_hibernation();
            break;
        case OBDH_COM_CMD_RF_MUTEX:
#if BEACON_MODE == DEBUG_MODE
            debug_print_msg("RF mutex command received!\n");
#endif // DEBUG_MODE
            if (beacon.flags.transmitting == true)
            {
#if BEACON_MODE == DEBUG_MODE
                debug_print_msg("All of our channels are busy now! (Elevator music starts)\n");
#endif // DEBUG_MODE
                obdh_com_send_data(OBDH_COM_BEACON_BUSY);
            }
            else
            {
#if BEACON_MODE == DEBUG_MODE
                debug_print_msg("RUN, FORREST, RUN!\n");
#endif // DEBUG_MODE
                obdh_com_send_data(OBDH_COM_BEACON_FREE);
                beacon.flags.can_transmit = false;
            }
            break;
        case OBDH_COM_TRANSCEIVER_FREE:
#if BEACON_MODE == DEBUG_MODE
            debug_print_msg("Beacon channel free command received!\n");
#endif // DEBUG_MODE
            beacon.flags.can_transmit = true;
            break;
        default:
#if BEACON_MODE == DEBUG_MODE
            debug_print_msg("ERROR! Invalid command!\n");
#endif // DEBUG_MODE
            break;
    }
}

static void obdh_com_receive_pkt(OBDH *obdh, uint8_t byte)
{
#if BEACON_MODE == DEBUG_MODE
    debug_print_msg("Packet data byte received!\n");
#endif // DEBUG_MODE
    obdh->buffer[obdh->byte_counter - OBDH_COM_BAT1_VOLTAGE_POS] = byte;
    obdh->byte_counter++;
}

void obdh_com_send_data(uint8_t data)
{
    // USCI_An TX buffer ready?
    while(!USCI_A_SPI_getInterruptStatus(OBDH_COM_SPI_BASE_ADDRESS, USCI_A_SPI_TRANSMIT_INTERRUPT))
    {
        
    }

    // Transmit data to master
    USCI_A_SPI_transmitData(OBDH_COM_SPI_BASE_ADDRESS, data);
}

static void obdh_com_save_data_from_buffer(uint8_t *buffer, OBDHData *obdh_data)
{
    uint8_t i = 0;
    uint8_t j = 0;
    
    for(i=0; i<OBDH_COM_BAT1_VOLTAGE_LEN; i++)
    {
        obdh_data->bat1_voltage[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_BAT2_VOLTAGE_LEN; i++)
    {
        obdh_data->bat2_voltage[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_SOLAR_PANELS_CURRENTS_LEN; i++)
    {
        obdh_data->solar_panels_currents[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_SOLAR_PANELS_VOLTAGES_LEN; i++)
    {
        obdh_data->solar_panels_voltages[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_BAT1_TEMPERATURE_LEN; i++)
    {
        obdh_data->bat1_temperature[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_BAT2_TEMPERATURE_LEN; i++)
    {
        obdh_data->bat2_temperature[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_IMU_LEN; i++)
    {
        obdh_data->imu[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_BAT1_CHARGE_LEN; i++)
    {
        obdh_data->bat1_charge[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_BAT2_CHARGE_LEN; i++)
    {
        obdh_data->bat2_charge[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_SYSTEM_TIME_LEN; i++)
    {
        obdh_data->system_time[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_SAT_STATUS_LEN; i++)
    {
        obdh_data->sat_status[i] = buffer[j++];
    }
    
    for(i=0; i<OBDH_COM_RESET_COUNTER_LEN; i++)
    {
        obdh_data->reset_counter[i] = buffer[j++];
    }
}

static void obdh_com_clear_buffer(uint8_t *buffer)
{
    memset(*buffer, OBDH_COM_DEFAULT_DATA_BYTE, OBDH_COM_DATA_PKT_LEN*sizeof(uint8_t));
}

/**
 * \fn USCI_A2_IST
 * 
 * \brief USCI_A2 interrupt vector service routine.
 * 
 * \return None
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A2_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A2_VECTOR)))
#endif
void USCI_A2_ISR()
{
    switch(__even_in_range(UCA2IV, 4))
    {
        //Vector 2 - RXIFG
        case 2:
            obdh_com_receive_data(obdh_ptr);
            break;
        default:
            break;
    }
}

//! \} End of obdh_com group