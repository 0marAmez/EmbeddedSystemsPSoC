/*******************************************************************************
* File Name: cyfitter_gpio.h
* 
* PSoC Creator  4.4
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef INCLUDED_CYFITTER_GPIO_H
#define INCLUDED_CYFITTER_GPIO_H
#include "cy_device_headers.h"

/* SW2 */
#define SW2_0_DRIVEMODE CY_GPIO_DM_PULLUP
#define SW2_0_INBUF_ENABLED 1u
#define SW2_0_INIT_DRIVESTATE 1u
#define SW2_0_INIT_MUXSEL 0u
#define SW2_0_INPUT_SYNC 2u
#define SW2_0_INTERRUPT_MODE CY_GPIO_INTR_FALLING
#define SW2_0_NUM 4u
#define SW2_0_PORT GPIO_PRT0
#define SW2_0_SLEWRATE CY_GPIO_SLEW_FAST
#define SW2_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define SW2_DRIVEMODE CY_GPIO_DM_PULLUP
#define SW2_INBUF_ENABLED 1u
#define SW2_INIT_DRIVESTATE 1u
#define SW2_INIT_MUXSEL 0u
#define SW2_INPUT_SYNC 2u
#define SW2_INTERRUPT_MODE CY_GPIO_INTR_FALLING
#define SW2_NUM 4u
#define SW2_PORT GPIO_PRT0
#define SW2_SLEWRATE CY_GPIO_SLEW_FAST
#define SW2_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* BLUE */
#define BLUE_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define BLUE_0_INBUF_ENABLED 0u
#define BLUE_0_INIT_DRIVESTATE 1u
#define BLUE_0_INIT_MUXSEL 8u
#define BLUE_0_INPUT_SYNC 2u
#define BLUE_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define BLUE_0_NUM 2u
#define BLUE_0_PORT GPIO_PRT7
#define BLUE_0_SLEWRATE CY_GPIO_SLEW_FAST
#define BLUE_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define BLUE_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define BLUE_INBUF_ENABLED 0u
#define BLUE_INIT_DRIVESTATE 1u
#define BLUE_INIT_MUXSEL 8u
#define BLUE_INPUT_SYNC 2u
#define BLUE_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define BLUE_NUM 2u
#define BLUE_PORT GPIO_PRT7
#define BLUE_SLEWRATE CY_GPIO_SLEW_FAST
#define BLUE_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* UART_rx */
#define UART_rx_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART_rx_0_INBUF_ENABLED 1u
#define UART_rx_0_INIT_DRIVESTATE 1u
#define UART_rx_0_INIT_MUXSEL 18u
#define UART_rx_0_INPUT_SYNC 2u
#define UART_rx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_rx_0_NUM 0u
#define UART_rx_0_PORT GPIO_PRT5
#define UART_rx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_rx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART_rx_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART_rx_INBUF_ENABLED 1u
#define UART_rx_INIT_DRIVESTATE 1u
#define UART_rx_INIT_MUXSEL 18u
#define UART_rx_INPUT_SYNC 2u
#define UART_rx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_rx_NUM 0u
#define UART_rx_PORT GPIO_PRT5
#define UART_rx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_rx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* UART_tx */
#define UART_tx_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART_tx_0_INBUF_ENABLED 0u
#define UART_tx_0_INIT_DRIVESTATE 1u
#define UART_tx_0_INIT_MUXSEL 18u
#define UART_tx_0_INPUT_SYNC 2u
#define UART_tx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_tx_0_NUM 1u
#define UART_tx_0_PORT GPIO_PRT5
#define UART_tx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_tx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART_tx_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART_tx_INBUF_ENABLED 0u
#define UART_tx_INIT_DRIVESTATE 1u
#define UART_tx_INIT_MUXSEL 18u
#define UART_tx_INPUT_SYNC 2u
#define UART_tx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_tx_NUM 1u
#define UART_tx_PORT GPIO_PRT5
#define UART_tx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_tx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

#endif /* INCLUDED_CYFITTER_GPIO_H */