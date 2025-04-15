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

/**
 * @file hal_flash.h
 * @brief Hardware Abstraction Layer for flash interface.
 *
 * This file contains the definitions and functions for the Flash hardware
 * abstraction layer.
 */

#ifndef HAL_FLASH_H_
#define HAL_FLASH_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "DRV_FLASH.h"

/**
 * @defgroup Custom Cloud Settings regions constants
 * @{
 */

extern char __MCU_CLOUD_SETTINGS_REGION_START_ADDRESS__; /*!< Flash offset start address of */
extern char __MCU_DEVICE_CERTIFICATE_REGION_START_ADDRESS__;   /*!< Flash offset of certificate data   */
extern char __MCU_PRIVATE_KEY_REGION_START_ADDRESS__;   /*!< Flash offset of private key */
extern char __MCU_ROOT_CERT_REGION_START_ADDRESS__;   /*!< Flash offset of root key */

/** @} drv_flash_constants */

  /**
   * @brief
   *
   * Custom MCU memory region size 10KB
   */

#define HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE  0x2800 / sizeof(unsigned int)

#define HAL_CLOUD_SETTINGS_REGION_START_ADDRESS  (unsigned int)&__MCU_CLOUD_SETTINGS_REGION_START_ADDRESS__

#define HAL_DEVICE_CERTIFICATE_REGION_START_ADDRESS (unsigned int)&__MCU_DEVICE_CERTIFICATE_REGION_START_ADDRESS__

#define HAL_PRIVATE_KEY_REGION_START_ADDRESS (unsigned int)&__MCU_PRIVATE_KEY_REGION_START_ADDRESS__

#define HAL_ROOT_CERT_REGION_START_ADDRESS (unsigned int)&__MCU_ROOT_CERT_REGION_START_ADDRESS__


  /**
   * @brief Read data from flash
   *
   * @param src Address to be read from flash
   * @param dst RAM space to store the data
   * @param size Data length to be read
   * @return Return the error code. Refer to @ref Flash_Err_Code.
   */
  extern uint8_t HAL_Flash_Data_Read(void *src, void *dst, size_t size);

  /**
   * @brief Initialize flash driver
   *
   * @return Return the error code. Refer to @ref Flash_Err_Code.
   */
  extern uint8_t HAL_Flash_Initialize(void);

  /**
   * @brief Uninitialize flash driver
   *
   * @return Return the error code. Refer to @ref Flash_Err_Code.
   */
  extern uint8_t HAL_Flash_Uninitialize(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_FLASH_H_ */
