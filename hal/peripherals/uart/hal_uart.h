
// /*
//  ***************************************************************************************************
//  * This file is part of Sensors SDK:
//  * https://www.we-online.com/sensors, https://github.com/WurthElektronik/Sensors-SDK_STM32
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
 * @file hal_uart.h
 * @brief UART Hardware Abstraction Layer (HAL) header file.
 *
 * This file contains the declarations and macros for the UART HAL,
 * providing an abstraction layer for UART operations.
 * 
 * The file uses include guards to prevent multiple inclusions of this header file.
 */


#ifndef HAL_UART_H_
#define HAL_UART_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "platform.h"
#include "serial.h"

/**
 * @brief Defines the external UART used for communication.
 * 
 * This macro defines the external UART interface that is currently active.
 * It is set to use ACTIVE_UARTF0 by default.
 * 
 * @note Modify ADRASTEA_EXTERNAL_UART to change the active UART interface.
 * 
 * @see ACTIVE_UARTF0 for more details on the specific UART interface.
 */
#define ADRASTEA_EXTERNAL_UART ACTIVE_UARTF0 

/**
 * @brief Defines the internal UART interface for Adrastea.
 *
 * This macro specifies the UART interface to be used internally within
 * the Adrastea module. It assigns the value of `ACTIVE_UARTI0` to the
 * internal UART interface, which can be utilized for serial communication
 * within the module.
 *
 * @see ACTIVE_UARTI0 for more details on the specific UART interface.
 */
#define ADRASTEA_INTERNAL_UART ACTIVE_UARTI0 

/**
 * @brief Defines the stack size for the HAL UART.
 *
 * This macro sets the stack size for the HAL UART. The stack size
 * is calculated as 512 bytes multiplied by 2, and then by 4, which
 * results in a total stack size of 4096 bytes.
 *
 * @note Ensure that the stack size is adequate for the application
 * requirements and the target hardware.
 */
#define HAL_UART_STACK_SIZE (512 * 2 * 4)

/**
 * @brief Size of the internal UART buffer.
 *
 * This macro defines the size of the internal UART buffer. The size is
 * calculated as 512 multiplied by 2, and then again multiplied by 2, 
 * resulting in a total buffer size of 2048 bytes.
 */
#define HAL_INTERNAL_UART_BUFFER_SIZE (512 * 2 * 2)

    /**
     * @brief Transmits data over UART with RX on pin 0 and TX on pin 1.
     *
     * This function sends a specified length of data over the UART interface,
     * using pin 0 for receiving and pin 1 for transmitting.
     *
     * @param[in] data Pointer to the data to be transmitted.
     * @param[in] dataLength The length of the data to be transmitted.
     */
    extern void HAL_UART_RXPin0_TXPin1_Transmit(const char *data, uint16_t dataLength);

    /**
     * @brief Reads data from the UART into a buffer.
     *
     * This function reads up to `len` bytes of data from the UART and stores
     * it in the provided buffer `buf`.
     *
     * @param[out] buf Pointer to the buffer where the read data will be stored.
     * @param[in] len Maximum number of bytes to read.
     * @return The number of bytes actually read.
     */
    extern uint32_t HAL_Internal_UART_Read(char *buf, uint32_t len);

    /**
     * @brief Reads data from an external UART interface.
     *
     * This function reads up to `len` bytes of data from the external UART interface and stores it in the provided buffer `buf`.
     *
     * @param[out] buf Pointer to the buffer where the read data will be stored.
     * @param[in] len The maximum number of bytes to read.
     * @return The number of bytes actually read, which could be less than `len` if fewer bytes are available.
     *
     * @note The function is designed to be non-blocking and will return immediately if no data is available.
     *
     * Example usage:
     * @code
     * char buffer[100];
     * uint32_t bytesRead = HAL_External_UART_Read(buffer, sizeof(buffer));
     * if (bytesRead > 0) {
     *     // Process the received data
     * }
     * @endcode
     */
    extern uint32_t HAL_External_UART_Read(char *buf, uint32_t len);

    /**
     * @brief Initializes the external UART hardware abstraction layer.
     *
     * This function performs the necessary setup to initialize the external UART
     * hardware abstraction layer. It prepares the UART interface for communication,
     * including configuring the UART peripheral and related hardware resources.
     *
     * @return int
     *         - Returns 0 on successful initialization.
     *         - Returns a negative value if initialization fails.
     *
     * @note This function must be called before any other UART operations can be performed.
     */
    extern int HAL_UART__External_Initialize(void);

    /**
     * @brief Initializes the internal UART hardware abstraction layer.
     *
     * This function performs the necessary setup and initialization of the UART
     * interface. It is intended for internal use within the HAL (Hardware
     * Abstraction Layer) and should not be called directly by application code.
     *
     * @return int
     *      - 0 on success
     *      - Negative error code on failure
     */
    extern int HAL_UART__Internal_Initialize(void);

    /**
     * @brief Starts internal UART communication.
     *
     * This function initializes and starts the UART communication for internal
     * purposes. It sets up the necessary UART configurations and enables the
     * communication channel.
     *
     * @return int32_t
     *         - 0 if the UART communication started successfully.
     *         - Negative value if there was an error starting the UART communication.
     */
    extern int32_t HAL_Start_Internal_UART_Communication(void);

    /**
     * @brief Writes data to the internal UART.
     *
     * This function sends the data contained in the buffer to the internal UART
     * for transmission. The function operates asynchronously and returns
     * immediately after initiating the write operation.
     *
     * @param[in] buffer Pointer to the buffer containing the data to be transmitted.
     *                   The buffer must be null-terminated.
     */
    extern void HAL_Write_Internal_Uart(char *buffer);

    /**
     * @brief Writes data to the external UART.
     *
     * This function sends the data contained in the provided buffer to the external UART.
     *
     * @param buffer Pointer to the buffer containing the data to be written.
     *
     * @note Ensure that the buffer is properly initialized and contains valid data before calling this function.
     */
    extern void HAL_Write_External_Uart(char *buffer);

    /**
     * @brief Retrieves the handle for the internal UART communication.
     *
     * This function returns the handle to be used for accessing the internal UART
     * communication interface. The handle allows interaction with the UART for
     * transmitting and receiving data.
     *
     * @return serial_handle The handle to the internal UART communication.
     */
    extern serial_handle HAL_Get_Internal_Uart_Handler(void);

    /**
     * @brief Retrieves the external UART handler.
     *
     * This function returns the handle to the external UART handler.
     * The handle allows access to configuration and data related to the
     * external UART module used in the hardware abstraction layer (HAL).
     *
     * @return serial_handle Handle to the external UART handler.
     */
    extern serial_handle HAL_Get_External_Uart_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_UART_H_ */
