
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


#ifndef SENSOR_APP_INCLUDE__H_
#define SENSOR_APP_INCLUDE__H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mini_console.h"
#include "config.h"

/** @brief Sensor-specific includes */
#include "WSEN_TIDS_2521020222501.h" ///< Temperature Sensor
#include "WSEN_PADS_2511020213301.h" ///< Pressure Sensor
#include "WSEN_ITDS_2533020201601.h" ///< Accelerometer Sensor
#include "WSEN_HIDS_2525020210002.h" ///< Humidity Sensor
#include "WSEN_HIDS_2525020210001.h" ///< Humidity Sensor

#include "Sensor_Data.h"

/** @brief Adrastea-specific includes */
#include "Adrastea.h"
#include "ATCommands/ATPacketDomain.h"
#include "ATCommands/ATMQTT.h"
#include "ATCommands/ATProprietary.h"
#include "ATCommands/ATSIM.h"
#include "ATCommands/ATDevice.h"
#include "ATProprietary.h"
#include "ATCommands/ATMQTT.h"
#include "ATCommands/ATEvent.h"

/**
 * @brief Initializes the sensors.
 */
extern void Init__Sensor();

/**
 * @brief Initializes the cloud communication.
 */
extern void Init__Cloud();

/**
 * @brief Retrieves the sensor data for device.
 *
 * This function queries the sensor data associated with the given device ID.
 *
 * @param device_id  string representing the device ID.
 * @return Sensor_Data_t The sensor data structure containing the latest readings from Sensors
 */
extern Sensor_Data_t Get_Sensor_Data(char* device_id);

#ifdef __cplusplus
}
#endif

#endif /* SENSOR_APP_INCLUDE__H_ */
