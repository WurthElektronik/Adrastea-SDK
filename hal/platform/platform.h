/*
 ***************************************************************************************************
 * This file is part of Sensors SDK:
 * https://www.we-online.com/sensors, https://github.com/WurthElektronik/Sensors-SDK_STM32
 *
 * THE SOFTWARE INCLUDING THE SOURCE CODE IS PROVIDED “AS IS”. YOU ACKNOWLEDGE THAT WÜRTH ELEKTRONIK
 * EISOS MAKES NO REPRESENTATIONS AND WARRANTIES OF ANY KIND RELATED TO, BUT NOT LIMITED
 * TO THE NON-INFRINGEMENT OF THIRD PARTIES’ INTELLECTUAL PROPERTY RIGHTS OR THE
 * MERCHANTABILITY OR FITNESS FOR YOUR INTENDED PURPOSE OR USAGE. WÜRTH ELEKTRONIK EISOS DOES NOT
 * WARRANT OR REPRESENT THAT ANY LICENSE, EITHER EXPRESS OR IMPLIED, IS GRANTED UNDER ANY PATENT
 * RIGHT, COPYRIGHT, MASK WORK RIGHT, OR OTHER INTELLECTUAL PROPERTY RIGHT RELATING TO ANY
 * COMBINATION, MACHINE, OR PROCESS IN WHICH THE PRODUCT IS USED. INFORMATION PUBLISHED BY
 * WÜRTH ELEKTRONIK EISOS REGARDING THIRD-PARTY PRODUCTS OR SERVICES DOES NOT CONSTITUTE A LICENSE
 * FROM WÜRTH ELEKTRONIK EISOS TO USE SUCH PRODUCTS OR SERVICES OR A WARRANTY OR ENDORSEMENT
 * THEREOF
 *
 * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
 * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE (license_terms_wsen_sdk.pdf)
 * LOCATED IN THE ROOT DIRECTORY OF THIS DRIVER PACKAGE.
 *
 * COPYRIGHT (c) 2022 Würth Elektronik eiSos GmbH & Co. KG
 *
 ***************************************************************************************************
 */

/**
 * @file
 * @brief Header file for platform-specific functions.
 */

#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include "global_types.h"

#include "SensorsSDK/WeSensorsSDK.h"

/* Read a register's content */
extern int8_t WE_ReadReg(WE_sensorInterface_t *interface,
                         uint8_t regAdr,
                         uint16_t numBytesToRead,
                         uint8_t *data);

/* Write a register's content */
extern int8_t WE_WriteReg(WE_sensorInterface_t *interface,
                          uint8_t regAdr,
                          uint16_t numBytesToWrite,
                          uint8_t *data);

/**
 * @brief This function provides minimum delay (in milliseconds) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay  specifies the delay time length, in milliseconds.
 * @retval None
 */
extern int8_t WE_isSensorInterfaceReady(WE_sensorInterface_t *interface);

/**
 * @brief This function provides minimum delay (in milliseconds) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay  specifies the delay time length, in milliseconds.
 * @retval None
 */
extern void WE_Test();

/**
 * @brief This function provides minimum delay (in milliseconds) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay  specifies the delay time length, in milliseconds.
 * @retval None
 */
extern uint32_t WE_GetTick();

 

/**
 * @brief This function provides minimum delay (in milliseconds) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay  specifies the delay time length, in milliseconds.
 * @retval None
 */
extern void WE_DelayMicroseconds(uint32_t sleepForUsec);

/**
 * @brief Retrieves the current tick count in microseconds.
 * 
 * This function returns the number of microseconds that have 
 * elapsed since the system started or a specific timer was 
 * initialized. It is typically used for timing and measuring 
 * time intervals in applications.
 * 
 * @return uint32_t The current tick count in microseconds.
 * 
 * @note The precision and range of the tick count are dependent 
 *       on the underlying hardware and system implementation. 
 *       Overflow may occur if the tick count exceeds the maximum 
 *       value of a 32-bit unsigned integer.
 */
extern uint32_t WE_GetTickMicroseconds();

/**
 * @brief Sends raw data to Adrastea via UART.
 *
 * This function sends data immediately without any processing and is used
 * internally for sending AT commands to Adrastea.
 *
 * @param[in] data Pointer to data buffer (data to be sent)
 * @param[in] dataLength Number of bytes to be sent
 */
extern void WE_UART_RXPin0_TXPin1_Transmit(const char *data, uint16_t dataLength);

/**
 * @brief Handles the reception of a byte via UART with RX on pin 0 and TX on pin 1.
 *
 * This function is called when a byte is received on the UART interface. It processes
 * the received byte and performs necessary actions based on the byte's value.
 *
 * @param receivedByte The byte received via UART.
 */
extern void WE_UART_RXPin0_TXPin1_HandleRxByte(uint8_t receivedByte);

/**
 * @brief This function provides minimum delay (in milliseconds) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay  specifies the delay time length, in milliseconds.
 * @retval None
 */
extern void WE_UART_RXPin0_TXPin1_Init(uint32_t baudrate,
                                       WE_FlowControl_t fc,
                                       WE_Parity_t par);
/**
 * @brief This function provides minimum delay (in milliseconds) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay  specifies the delay time length, in milliseconds.
 * @retval None
 */
extern void WE_DEBUG_PRINT(char *data);

/**
 * @brief This function provides minimum delay (in milliseconds) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay  specifies the delay time length, in milliseconds.
 * @retval None
 */
extern bool WE_InitPins(WE_Pin_t pins[], uint8_t numPins);

/**
 * @brief This function provides minimum delay (in milliseconds) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay  specifies the delay time length, in milliseconds.
 * @retval None
 */
extern bool WE_SetPin(WE_Pin_t pin, WE_Pin_Level_t out);

#endif /* PLATFORM_H_INCLUDED */
