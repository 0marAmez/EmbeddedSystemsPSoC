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

/* Echo */
#define Echo_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define Echo_0_INBUF_ENABLED 1u
#define Echo_0_INIT_DRIVESTATE 0u
#define Echo_0_INIT_MUXSEL 0u
#define Echo_0_INPUT_SYNC 2u
#define Echo_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define Echo_0_NUM 3u
#define Echo_0_PORT GPIO_PRT9
#define Echo_0_SLEWRATE CY_GPIO_SLEW_FAST
#define Echo_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define Echo_DRIVEMODE CY_GPIO_DM_HIGHZ
#define Echo_INBUF_ENABLED 1u
#define Echo_INIT_DRIVESTATE 0u
#define Echo_INIT_MUXSEL 0u
#define Echo_INPUT_SYNC 2u
#define Echo_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define Echo_NUM 3u
#define Echo_PORT GPIO_PRT9
#define Echo_SLEWRATE CY_GPIO_SLEW_FAST
#define Echo_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* I2C_scl */
#define I2C_scl_0_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define I2C_scl_0_INBUF_ENABLED 1u
#define I2C_scl_0_INIT_DRIVESTATE 1u
#define I2C_scl_0_INIT_MUXSEL 19u
#define I2C_scl_0_INPUT_SYNC 2u
#define I2C_scl_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define I2C_scl_0_NUM 4u
#define I2C_scl_0_PORT GPIO_PRT6
#define I2C_scl_0_SLEWRATE CY_GPIO_SLEW_FAST
#define I2C_scl_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define I2C_scl_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define I2C_scl_INBUF_ENABLED 1u
#define I2C_scl_INIT_DRIVESTATE 1u
#define I2C_scl_INIT_MUXSEL 19u
#define I2C_scl_INPUT_SYNC 2u
#define I2C_scl_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define I2C_scl_NUM 4u
#define I2C_scl_PORT GPIO_PRT6
#define I2C_scl_SLEWRATE CY_GPIO_SLEW_FAST
#define I2C_scl_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* I2C_sda */
#define I2C_sda_0_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define I2C_sda_0_INBUF_ENABLED 1u
#define I2C_sda_0_INIT_DRIVESTATE 1u
#define I2C_sda_0_INIT_MUXSEL 19u
#define I2C_sda_0_INPUT_SYNC 2u
#define I2C_sda_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define I2C_sda_0_NUM 5u
#define I2C_sda_0_PORT GPIO_PRT6
#define I2C_sda_0_SLEWRATE CY_GPIO_SLEW_FAST
#define I2C_sda_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define I2C_sda_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define I2C_sda_INBUF_ENABLED 1u
#define I2C_sda_INIT_DRIVESTATE 1u
#define I2C_sda_INIT_MUXSEL 19u
#define I2C_sda_INPUT_SYNC 2u
#define I2C_sda_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define I2C_sda_NUM 5u
#define I2C_sda_PORT GPIO_PRT6
#define I2C_sda_SLEWRATE CY_GPIO_SLEW_FAST
#define I2C_sda_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

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

/* Pin_US_Trigger */
#define Pin_US_Trigger_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define Pin_US_Trigger_0_INBUF_ENABLED 0u
#define Pin_US_Trigger_0_INIT_DRIVESTATE 1u
#define Pin_US_Trigger_0_INIT_MUXSEL 8u
#define Pin_US_Trigger_0_INPUT_SYNC 2u
#define Pin_US_Trigger_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define Pin_US_Trigger_0_NUM 2u
#define Pin_US_Trigger_0_PORT GPIO_PRT9
#define Pin_US_Trigger_0_SLEWRATE CY_GPIO_SLEW_FAST
#define Pin_US_Trigger_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define Pin_US_Trigger_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define Pin_US_Trigger_INBUF_ENABLED 0u
#define Pin_US_Trigger_INIT_DRIVESTATE 1u
#define Pin_US_Trigger_INIT_MUXSEL 8u
#define Pin_US_Trigger_INPUT_SYNC 2u
#define Pin_US_Trigger_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define Pin_US_Trigger_NUM 2u
#define Pin_US_Trigger_PORT GPIO_PRT9
#define Pin_US_Trigger_SLEWRATE CY_GPIO_SLEW_FAST
#define Pin_US_Trigger_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

#endif /* INCLUDED_CYFITTER_GPIO_H */