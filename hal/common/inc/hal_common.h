// /*
//  ***************************************************************************************************
//  * Würth Elektronik eiSos GmbH & Co. KG
//  * https://www.we-online.com
//  *
//  * THE SOFTWARE INCLUDING THE SOURCE CODE IS PROVIDED “AS IS”. YOU ACKNOWLEDGE THAT WÜRTH ELEKTRONIK
//  * EISOS MAKES NO REPRESENTATIONS AND WARRANTIES OF ANY KIND RELATED TO, BUT NOT LIMITED
//  * TO THE NON-INFRINGEMENT OF THIRD PARTIES’ INTELLECTUAL PROPERTY RIGHTS OR THE
//  * MERCHANTABILITY OR FITNESS FOR YOUR INTENDED PURPOSE OR USAGE. WÜRTH ELEKTRONIK EISOS DOES NOT
//  * WARRANT OR REPRESENT THAT ANY LICENSE, EITHER EXPRESS OR IMPLIED, IS GRANTED UNDER ANY PATENT
//  * RIGHT, COPYRIGHT, MASK WORK RIGHT, OR OTHER INTELLECTUAL PROPERTY RIGHT RELATING TO ANY
//  * COMBINATION, MACHINE, OR PROCESS IN WHICH THE PRODUCT IS USED. INFORMATION PUBLISHED BY
//  * WÜRTH ELEKTRONIK EISOS REGARDING THIRD-PARTY PRODUCTS OR SERVICES DOES NOT CONSTITUTE A LICENSE
//  * FROM WÜRTH ELEKTRONIK EISOS TO USE SUCH PRODUCTS OR SERVICES OR A WARRANTY OR ENDORSEMENT
//  * THEREOF
//  *
//  * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
//  * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE (license_terms_wsen_sdk.pdf)
//  * LOCATED IN THE ROOT DIRECTORY OF THIS DRIVER PACKAGE.
//  *
//  * COPYRIGHT (c) 2024 Würth Elektronik eiSos GmbH & Co. KG
//  *
//  ***************************************************************************************************
//  */

#ifndef HAL_COMMON_H_
#define HAL_COMMON_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*Standart libraries*/
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/*FreeRTOS Includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stack_macros.h"
#include "assert.h"

/*Middleware*/
#include "alt_osal.h"
#include "cmsis_os2.h"
#include "serial.h"
#include <newlibPort.h>

/*HAL Configuration */
#include "hal_config.h"

#ifdef HAL_I2C_MODULE_ENABLED_ALT1250
#include "hal_i2c.h"
#endif

#ifdef HAL_SPI_CONFIG_ENABLED_ALT1250
#include "hal_spi.h"
#endif

#ifdef HAL_SIM_CONFIG_ENABLED_ALT1250
#include "hal_sim.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED_ALT1250
#include "hal_uart.h"
#endif

#ifdef HAL_FLASH_MODULE_ENABLED
#include "hal_flash.h"
#endif

#ifdef HAL_ADC_CONFIG_ENABLED_ALT1250
#include "hal_adc.h"
#endif

#ifdef HAL_RF_CONFIG_ENABLED_ALT1250
#include "hal_rf.h"
#endif

  /**
   * @brief HAL Status structures definition
   *
   * This enum defines the various statuses that can be returned by HAL functions.
   */
  typedef enum
  {
    HAL_OK = 0x00U,     /**< Operation is successful */
    HAL_ERROR = 0x01U,  /**< Operation resulted in an error */
    HAL_BUSY = 0x02U,   /**< Operation is currently in progress */
    HAL_TIMEOUT = 0x03U /**< Operation timed out */
  } HAL_StatusTypeDef;

/**
 * @def I2C_MEMADD_SIZE_8BIT
 * @brief I2C memory address size is 8 bits.
 *
 * This macro defines the I2C memory address size to be 8 bits. It is used to
 * configure the memory address size in I2C communication.
 */
#define I2C_MEMADD_SIZE_8BIT (0x00000001U)

/**
 * @def I2C_MEMADD_SIZE_16BIT
 * @brief I2C memory address size is 16 bits.
 *
 * This macro defines the I2C memory address size to be 16 bits. It is used to
 * configure the memory address size in I2C communication.
 */
#define I2C_MEMADD_SIZE_16BIT (0x00000002U)

#include "platform.h"

#ifdef __cplusplus
}
#endif

#endif
