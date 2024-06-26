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
 * @file hal_helper.h
 * @brief Hardware Abstraction Layer (HAL) Helper Functions
 *
 * This header file contains the declarations for helper functions
 * used in the Hardware Abstraction Layer (HAL). These functions
 * provide various utility operations to facilitate interaction
 * with hardware components in a platform-independent manner.
 */

#ifndef HAL_HALPER_H_
#define HAL_HELPER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

    /**
     * @brief  This function provides a delay for the specified number of milliseconds.
     * @param  Delay: specifies the delay time length, in milliseconds.
     * @retval None
     */
    extern void HAL_Delay(uint32_t Delay);

    /**
     * @brief Returns the current tick count.
     *
     * This function retrieves the current system tick count in milliseconds.
     * The tick count value wraps around after reaching its maximum value.
     *
     * @return uint32_t Current tick count in milliseconds.
     */
    extern uint32_t HAL_GetTick();

    /**
     * @brief Delays the program execution for the specified number of microseconds.
     *
     * @param sleepForUsec Number of microseconds to delay.
     *
     * @note This function provides a delay using a busy-wait mechanism.
     *       The actual delay may be approximate depending on the system's clock accuracy.
     */
    extern void HAL_DelayMicroseconds(uint32_t sleepForUsec);

    /**
     * @brief Returns the current system tick in microseconds.
     *
     * This function retrieves the current system tick value in microseconds
     * since some reference point (e.g., system start-up). The resolution and
     * accuracy depend on the HAL implementation.
     *
     * @return uint32_t Current system tick in microseconds.
     */
    extern uint32_t HAL_GetTickMicroseconds();

#ifdef __cplusplus
}
#endif

#endif /* HAL_HELPER_H_ */
