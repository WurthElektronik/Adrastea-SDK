/*  ---------------------------------------------------------------------------

    (c) copyright 2021 Altair Semiconductor, Ltd. All rights reserved.

    This software, in source or object form (the "Software"), is the
    property of Altair Semiconductor Ltd. (the "Company") and/or its
    licensors, which have all right, title and interest therein, You
    may use the Software only in  accordance with the terms of written
    license agreement between you and the Company (the "License").
    Except as expressly stated in the License, the Company grants no
    licenses by implication, estoppel, or otherwise. If you are not
    aware of or do not agree to the License terms, you may not use,
    copy or modify the Software. You may use the source code of the
    Software only for your internal purposes and may not distribute the
    source code of the Software, any part thereof, or any derivative work
    thereof, to any third party, except pursuant to the Company's prior
    written consent.
    The Software is the confidential information of the Company.

   ------------------------------------------------------------------------- */


/**************************************************

Automatic Generated H file: DON'T EDIT MANUALLY!

***************************************************/

#ifndef ALT1255_IF_CONFIG_H
#define ALT1255_IF_CONFIG_H
#include "if_cfg/general_config.h"
#include "if_cfg/stubs_config.h"

/***************************************/
/* Magic Random Synchronization Number */
/***************************************/

#define IO_PAR_SYNC_NUMBER	ALT1255_IO_PAR_SYNC_UNDEFINED

/********************************/
/* UART Interfaces Configuration */
/********************************/

/****************************************************************************
 *  UART configurations for ALT1255 MCU.
 *  This configuration should reference DRV_UART.h
 *  ------------------------------------------------------------------------
 *  Baudrate definitions:
 *  ------------------------------------------------------------------------
 *  typedef enum {
 *      DRV_UART_BAUD_110 = 110,
 *      DRV_UART_BAUD_1200 = 1200,
 *      DRV_UART_BAUD_2400 = 2400,
 *      DRV_UART_BAUD_9600 = 9600,
 *      DRV_UART_BAUD_14400 = 14400,
 *      DRV_UART_BAUD_19200 = 19200,
 *      DRV_UART_BAUD_38400 = 38400,
 *      DRV_UART_BAUD_57600 = 57600,
 *      DRV_UART_BAUD_76800 = 76800,
 *      DRV_UART_BAUD_115200 = 115200,
 *      DRV_UART_BAUD_230400 = 230400,
 *      DRV_UART_BAUD_460800 = 460800,
 *      DRV_UART_BAUD_921600 = 921600,
 *      DRV_UART_BAUD_1843200 = 1843200,
 *      DRV_UART_BAUD_3686400 = 3686400,
 * } DRV_UART_Baudrate;
 *  ------------------------------------------------------------------------
 *  HWFLOWCTL definitions:
 *  ------------------------------------------------------------------------
 *  typedef enum {
 *      DRV_UART_HWCONTROL_NONE = 0U,
 *      DRV_UART_HWCONTROL_RTS = 1U,
 *      DRV_UART_HWCONTROL_CTS = 2U,
 *      DRV_UART_HWCONTROL_RTS_CTS = 3U,
 *   } DRV_UART_Hardware_Flow_Control;
 *  ------------------------------------------------------------------------
 *  PARITY definitions
 *  ------------------------------------------------------------------------
 *  typedef enum {
 *      DRV_UART_PARITY_MODE_ZERO = 0,
 *      DRV_UART_PARITY_MODE_ONE = 1,
 *      DRV_UART_PARITY_MODE_ODD = 2,
 *      DRV_UART_PARITY_MODE_EVEN = 3,
 *      DRV_UART_PARITY_MODE_DISABLE = 4,
 *  } DRV_UART_Parity;
 *  ------------------------------------------------------------------------
 *  STOPBITS definitions
 *  ------------------------------------------------------------------------
 *  typedef enum {
 *      DRV_UART_STOP_BITS_1 = 0,
 *      DRV_UART_STOP_BITS_2 = 1,
 *  } DRV_UART_Stop_Bits;
 *  ------------------------------------------------------------------------
 *  WORDLENGTH definitions
 *  ------------------------------------------------------------------------
 *  typedef enum {
 *      DRV_UART_WORD_LENGTH_5B = 0,
 *      DRV_UART_WORD_LENGTH_6B = 1,
 *      DRV_UART_WORD_LENGTH_7B = 2,
 *      DRV_UART_WORD_LENGTH_8B = 3,
 *  } DRV_UART_Word_Length;
 *  ------------------------------------------------------------------------
******************************************************************************/

/* UARTF0 */
/**********/

/* Pins configuration */
#define UARTF0_RX_PIN_SET	ALT1255_GPIO23
#define UARTF0_TX_PIN_SET	ALT1255_GPIO24
#define UARTF0_RTS_PIN_SET	ALT1255_GPIO26
#define UARTF0_CTS_PIN_SET	ALT1255_GPIO25

/* Interface configuration */
#define UARTF0_BAUDRATE_DEFAULT		DRV_UART_BAUD_115200
#define UARTF0_HWFLOWCTRL_DEFAULT	DRV_UART_HWCONTROL_NONE
#define UARTF0_PARITY_DEFAULT		DRV_UART_PARITY_MODE_DISABLE
#define UARTF0_STOPBITS_DEFAULT		DRV_UART_STOP_BITS_1
#define UARTF0_WORDLENGTH_DEFAULT	DRV_UART_WORD_LENGTH_8B

/**************************************/
/* SPI Interfaces Configuration */
/**************************************/

/****************************************************************************
 *  SPI configurations for ALT1255
 *  This configuration should reference spi.h
 *  ------------------------------------------------------------------------
 *  CPHA definitions
 *  ------------------------------------------------------------------------
 *  typedef enum spi_clock_phase {
 *      SPI_CPHA_0 = 0,
 *      SPI_CPHA_1 = 1,
 *  } SPI_Clock_Phase;
 *  ------------------------------------------------------------------------
 *  CPOL definitions
 *  ------------------------------------------------------------------------
 *  typedef enum spi_clock_polarity {
 *      SPI_CPOL_0 = 0,
 *      SPI_CPOL_1 = 1,
 *  } SPI_Clock_Polarity;
 *  ------------------------------------------------------------------------
 *  ENDIAN definitions
 *  ------------------------------------------------------------------------
 *  typedef enum spi_endian {
 *      SPI_BIG_ENDIAN,
 *      SPI_LITTLE_ENDIAN,
 *  } SPI_Endian;
 *  ------------------------------------------------------------------------
 *  BITORDER definitions
 *  ------------------------------------------------------------------------
 *  typedef enum spi_bit_order {
 *      SPI_BIT_ORDER_MSB_FIRST,
 *      SPI_BIT_ORDER_LSB_FIRST,
 *  } SPI_Bit_Order;
 *  ------------------------------------------------------------------------
 *  BUSSPEED definitions
 *  ------------------------------------------------------------------------
 *  This is a configurable value, this value should be set according to the
 *  application.
 *  ------------------------------------------------------------------------
 *  DATABITS definitions
 *  ------------------------------------------------------------------------
 *  This is a configurable value, this value should be set according to the
 *  application.
 *  ------------------------------------------------------------------------
 *  SSMODE definitions
 *  ------------------------------------------------------------------------
 *  typedef enum spi_ss_mode {
 *      SPI_SS_ACTIVE_LOW,
 *      SPI_SS_ACTIVE_HIGH,
 *  } SPI_SS_Mode;
 *  ------------------------------------------------------------------------
******************************************************************************/

/* SPIM0 */
/*********/

/* Pins configuration */
#define SPIM0_CLK_PIN_SET	ALT1255_PIN_UNDEFINED
#define SPIM0_EN_PIN_SET	ALT1255_PIN_UNDEFINED
#define SPIM0_MISO_PIN_SET	ALT1255_PIN_UNDEFINED
#define SPIM0_MOSI_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define SPIM0_CPHA_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define SPIM0_CPOL_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define SPIM0_ENDIAN_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define SPIM0_BITORDER_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define SPIM0_BUSSPEED_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define SPIM0_DATABITS_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define SPIM0_SSMODE_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* SPIS0 */
/*********/

/* Pins configuration */
#define SPIS0_CLK_PIN_SET	ALT1255_PIN_UNDEFINED
#define SPIS0_MRDY_PIN_SET	ALT1255_PIN_UNDEFINED
#define SPIS0_SRDY_PIN_SET	ALT1255_PIN_UNDEFINED
#define SPIS0_MISO_PIN_SET	ALT1255_PIN_UNDEFINED
#define SPIS0_MOSI_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define SPIS0_CPHA_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define SPIS0_CPOL_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define SPIS0_ENDIAN_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define SPIS0_SSMODE_DEFAULT	ALT1255_CONFIG_UNDEFINED

/*******************************/
/* I2C Interfaces Configuration */
/*******************************/

/* I2C-0 */
/*********/

/* Pins configuration */
#define I2C0_SDA_PIN_SET	ALT1255_PIN_UNDEFINED
#define I2C0_SCL_PIN_SET	ALT1255_PIN_UNDEFINED

/********************************/
/* GPIO Interfaces Configuration */
/********************************/


/****************************************************************************
 *  GPIO configurations for ALT1255
 *  This configuration should reference DRV_GPIO.h
 *  ------------------------------------------------------------------------
 *  GPIO direction definitions
 *  ------------------------------------------------------------------------
 *  typedef enum {
 *      GPIO_DIR_INPUT=0,
 *      GPIO_DIR_OUTPUT
 *  }GPIO_Direction;
 *  ------------------------------------------------------------------------
 *  GPIO pull mode definitions
 *  ------------------------------------------------------------------------
 *  typedef enum {
 *      GPIO_PULL_NONE=0,
 *      GPIO_PULL_UP,
 *      GPIO_PULL_DOWN
 *  }GPIO_Pull;
 *  ------------------------------------------------------------------------
 *  GPIO initial output value definition
 *  ------------------------------------------------------------------------
 *  (0) or (1)
 *  ------------------------------------------------------------------------
******************************************************************************/

/* GPIO_ID_01 */
/**************/

/* Pins configuration */
#define GPIO_ID_01_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_01_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_01_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_01_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_02 */
/**************/

/* Pins configuration */
#define GPIO_ID_02_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_02_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_02_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_02_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_03 */
/**************/

/* Pins configuration */
#define GPIO_ID_03_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_03_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_03_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_03_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_04 */
/**************/

/* Pins configuration */
#define GPIO_ID_04_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_04_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_04_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_04_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_05 */
/**************/

/* Pins configuration */
#define GPIO_ID_05_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_05_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_05_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_05_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_06 */
/**************/

/* Pins configuration */
#define GPIO_ID_06_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_06_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_06_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_06_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_07 */
/**************/

/* Pins configuration */
#define GPIO_ID_07_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_07_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_07_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_07_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_08 */
/**************/

/* Pins configuration */
#define GPIO_ID_08_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_08_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_08_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_08_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_09 */
/**************/

/* Pins configuration */
#define GPIO_ID_09_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_09_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_09_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_09_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_10 */
/**************/

/* Pins configuration */
#define GPIO_ID_10_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_10_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_10_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_10_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_11 */
/**************/

/* Pins configuration */
#define GPIO_ID_11_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_11_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_11_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_11_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_12 */
/**************/

/* Pins configuration */
#define GPIO_ID_12_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_12_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_12_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_12_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_13 */
/**************/

/* Pins configuration */
#define GPIO_ID_13_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_13_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_13_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_13_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_14 */
/**************/

/* Pins configuration */
#define GPIO_ID_14_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_14_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_14_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_14_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/* GPIO_ID_15 */
/**************/

/* Pins configuration */
#define GPIO_ID_15_PIN_SET	ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define GPIO_ID_15_DIR_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_15_PU_DEFAULT	ALT1255_CONFIG_UNDEFINED
#define GPIO_ID_15_VAL_DEFAULT	ALT1255_CONFIG_UNDEFINED

/**************************************/
/* Wakeup Source Configuration */
/**************************************/

/****************************************************************************
 *  Wakeup source configurations for ALT1255
 *  This configuration should reference DRV_PM.h
 *  ------------------------------------------------------------------------
 *  PM wakeup PIN mode/polarity definitions
 *  ------------------------------------------------------------------------
 *  typedef enum {
 *      DRV_PM_WAKEUP_EDGE_RISING,
 *      DRV_PM_WAKEUP_EDGE_FALLING,
 *      DRV_PM_WAKEUP_EDGE_RISING_FALLING,
 *      DRV_PM_WAKEUP_LEVEL_POL_HIGH,
 *      DRV_PM_WAKEUP_LEVEL_POL_LOW,
 *  } DRV_PM_WAKEUP_PinPolarity;
 *  ------------------------------------------------------------------------
******************************************************************************/

/* WAKEUP_IO_ID_01 */
/*******************/

/* Pins configuration */
#define WAKEUP_IO_ID_01_PIN_SET            ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define WAKEUP_IO_ID_01_PIN_POL            ALT1255_CONFIG_UNDEFINED

/* WAKEUP_IO_ID_02 */
/*******************/

/* Pins configuration */
#define WAKEUP_IO_ID_02_PIN_SET            ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define WAKEUP_IO_ID_02_PIN_POL            ALT1255_CONFIG_UNDEFINED

/* WAKEUP_IO_ID_03 */
/*******************/

/* Pins configuration */
#define WAKEUP_IO_ID_03_PIN_SET            ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define WAKEUP_IO_ID_03_PIN_POL            ALT1255_CONFIG_UNDEFINED

/* WAKEUP_IO_ID_04 */
/*******************/

/* Pins configuration */
#define WAKEUP_IO_ID_04_PIN_SET            ALT1255_PIN_UNDEFINED

/* Interface configuration */
#define WAKEUP_IO_ID_04_PIN_POL            ALT1255_CONFIG_UNDEFINED


/**************************************/
/* LED Configuration */
/**************************************/


/* LED0 */
/**********/

/* Pins configuration */
#define LED0_PIN_SET	ALT1255_PIN_UNDEFINED

/* LED1 */
/**********/

/* Pins configuration */
#define LED1_PIN_SET	ALT1255_PIN_UNDEFINED

/* LED2 */
/**********/

/* Pins configuration */
#define LED2_PIN_SET	ALT1255_PIN_UNDEFINED

/**************************************/
/* PWM Configuration */
/**************************************/

/* PWM0 */

/* Pins configuration */
#define PWM0_PIN_SET	ALT1255_PIN_UNDEFINED

/* PWM1 */

/* Pins configuration */
#define PWM1_PIN_SET	ALT1255_PIN_UNDEFINED

#endif /* ALT1255_IF_CONFIG_H*/
