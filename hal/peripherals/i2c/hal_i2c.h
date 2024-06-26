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
 * @file hal_i2c.h
 * @brief Hardware Abstraction Layer for I2C interface.
 *
 * This file contains the definitions and functions for the I2C hardware
 * abstraction layer.
 */

#ifndef HAL_I2C_H_
#define HAL_I2C_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cmsis_os2.h"
#include "DRV_I2C.h"

  /**
   * @brief Enumeration for I2C Operation Modes.
   *
   * This enumeration defines the different operation modes for the I2C (Inter-Integrated Circuit) interface.
   */
  typedef enum
  {
    OPMODE_NONBLOCK, /**< Non-blocking operation mode. The I2C operation will not block the calling thread. */
    OPMODE_BLOCK,    /**< Blocking operation mode. The I2C operation will block the calling thread until completion. */
    OPMODE_MAX,      /**< Maximum value for I2C operation modes. Used for validation purposes. */
  } I2C_OpMode;

  /**
   * @enum HAL_I2C_BusId
   * @brief Enumeration for I2C bus identifiers.
   *
   * This enumeration defines the identifiers for the available I2C buses.
   */
  typedef enum
  {
    HAL_I2C_BusId_0, /**< Identifier for I2C bus 0 */
    HAL_I2C_BusId_1  /**< Identifier for I2C bus 1 */
  } HAL_I2C_BusId;

  /**
   * @brief Enumerates the power modes for the I2C hardware abstraction layer (HAL).
   *
   * This enumeration defines the possible power states for the I2C interface.
   */
  typedef enum
  {
    HAL_I2C_POWER_OFF,  /**< Power off mode. The I2C interface is powered down. */
    HAL_I2C_POWER_FULL, /**< Full power mode. The I2C interface is fully powered. */
  } HAL_I2C_PowerMode;

  /**
   * @brief Set the I2C Bus ID.
   *
   * This function sets the I2C bus identifier to the specified value.
   *
   * @param busId The identifier for the I2C bus. It is of type HAL_I2C_BusId.
   *
   * @return uint8_t Returns 0 on success, non-zero error code on failure.
   */
  extern uint8_t HAL_I2C__Set_I2C_Bus_Id(HAL_I2C_BusId busId);

  /**
   * @brief  Initializes the I2C peripheral.
   *
   * This function configures the necessary settings and initializes the I2C
   * peripheral for communication. It must be called before using any other
   * I2C functions.
   *
   * @return uint8_t
   *         - 0 if initialization is successful.
   *         - 1 if there is an error during initialization.
   */
  extern uint8_t HAL_I2C__Initialize(void);

  /**
   * @brief  Sets the I2C communication speed.
   *
   * This function configures the I2C peripheral to operate at the specified speed.
   * The speed parameter is typically given in hertz (Hz) and represents the clock
   * speed of the I2C bus.
   *
   * @param  speed The desired I2C communication speed in hertz (Hz).
   *
   * @return uint8_t Returns 0 if the speed was set successfully, or a non-zero
   *                 error code if the operation failed.
   */
  extern uint8_t HAL__I2C_SetSpeed(uint32_t speed);

  /**
   * @brief Sets the operational mode for the I2C peripheral.
   *
   * This function configures the I2C peripheral to operate in the specified mode.
   *
   * @param[in] opMode The desired operational mode for the I2C peripheral.

   *
   * @return uint8_t Status of the operation.
   *                 - 0: Success
   *                 - 1: Invalid mode
   *                 - 2: Peripheral busy
   */
  extern uint8_t HAL__I2C_SetOpMode(uint8_t opMode);

  /**
   * @brief Uninitializes the I2C peripheral.
   *
   * This function performs the necessary cleanup to uninitialize the I2C
   * peripheral. It ensures that the I2C peripheral is properly shut down,
   * and any resources allocated for the I2C communication are released.
   *
   * @return uint8_t
   * @retval 0 if the operation was successful.
   * @retval 1 if there was an error during uninitialization.
   *
   * @note This function should be called when the I2C peripheral is no
   * longer needed to free up system resources.
   */
  extern uint8_t HAL_I2C__Uninitialize(void);

  /**
   * @brief Sets the power mode of the HAL I2C interface.
   *
   * This function sets the power mode of the HAL I2C interface to the specified
   * mode.
   *
   * @param powerMode The power mode to set for the HAL I2C interface.
   *        - HAL_I2C_POWER_OFF: Off mode.
   *        - HAL_I2C_POWER_FULL: Full operating mode.
   *
   * @return uint8_t Returns 0 on success, or an error code if the operation fails.
   *
   * @note This function is platform-dependent and may have specific requirements
   *       or limitations on the power modes supported.
   */
  extern uint8_t HAL_I2C__SetPowerMode(HAL_I2C_PowerMode powerMode);

  /**
   * @brief Reads a block of data from a specified memory address of an I2C device.
   * @param DevAddress: I2C device address (7-bit or 10-bit).
   * @param MemAddress: Starting memory address to read from.
   * @param MemAddSize: Size of the memory address in bytes
   * @param pData: Pointer to data buffer where read data will be stored.
   * @param Size: Number of bytes to read.
   * @param Timeout: Timeout duration in milliseconds.
   * @return HAL status (HAL_OK if operation is successful, HAL_ERROR otherwise).
   *
   * This function reads a block of data from a specified memory address of an I2C device.
   * The memory address size is specified by MemAddSize parameter
   * pData should point to a buffer large enough to store Size bytes of data.
   * Timeout specifies the maximum time to wait for the operation to complete.
   */
  extern uint8_t HAL_I2C_Mem_Read(uint16_t DevAddress, uint16_t MemAddress,
                                  uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

  /**
   * @brief  Receives data in master mode through the I2C bus.
   *
   * This function handles the reception of data from a specified I2C device
   * in master mode.
   *
   * @param  DevAddress  The address of the I2C device from which data is to be received.
   * @param  pData       Pointer to the buffer where the received data will be stored.
   * @param  Size        The number of bytes to be received.
   * @param  Timeout     The maximum time in milliseconds the function will wait for the reception to complete.
   *
   * @retval uint8_t     Returns a status code indicating the success or failure of the reception.
   *                     - 0: Success
   *                     - 1: Timeout
   *                     - 2: Error
   */
  extern uint8_t HAL_I2C_Master_Receive(uint16_t DevAddress, uint8_t *pData,
                                        uint16_t Size, uint32_t Timeout);

  /**
   * @brief  Writes data to a specific memory address of a device over I2C.
   *
   * This function transmits data to a memory address of an I2C device.
   *
   * @param  DevAddress  I2C device address.
   * @param  MemAddress  Internal memory address to write to.
   * @param  MemAddSize  Size of internal memory address. This parameter can be 8-bit or 16-bit.
   * @param  pData       Pointer to data buffer to be written.
   * @param  Size        Amount of data to be written.
   * @param  Timeout     Timeout duration.
   *
   * @retval uint8_t     Returns status of the operation.
   */
  extern uint8_t HAL_I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress,
                                   uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

  /**
   * @brief  Checks if the I2C device is ready for communication.
   *
   * This function checks whether the I2C device at the specified address is ready for communication.
   * It tries to communicate with the device a specified number of times within a timeout period.
   *
   * @param  DevAddress I2C address of the target device.
   * @param  Trials Number of trials to check the device's readiness.
   * @param  Timeout Timeout duration for each trial in milliseconds.
   * @retval uint8_t Returns 1 if the device is ready, 0 if the device is not ready or an error occurred.
   */
   extern uint8_t HAL_I2C_IsDeviceReady(uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* HAL_I2C_H_ */
