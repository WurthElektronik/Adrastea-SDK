

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

#ifndef SENSOR_DATA_INCLUDE__H_
#define SENSOR_DATA_INCLUDE__H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cJSON.h"

/** @typedef Device_Id_t
 *  @brief Defines a device identifier as a character pointer.
 */
typedef char* Device_Id_t;

typedef float HIDS_Humidity_Value_t, HIDS_Temperature_Value_t;
typedef float TIDS_Temperature_t;
typedef float ITDS_Temperature_t, ITDS_X_t, ITDS_Y_t, ITDS_Z_t;
typedef float PADS_Temperature_Float_t, PADS_Pressure_t;
typedef float PADS_Temperature_Int_t;

/**
 * @struct HIDS_Data_t
 * @brief Represents humidity and temperature data from the HIDS sensor.
 */
typedef struct HIDS_Data_t {
    HIDS_Humidity_Value_t humidity;  /**< Humidity value */
    HIDS_Temperature_Value_t temperature; /**< Temperature value */
} HIDS_Data_t;

/**
 * @struct TIDS_Data_t
 * @brief Represents temperature data from the TIDS sensor.
 */
typedef struct TIDS_Data_t {
    TIDS_Temperature_t temperature; /**< Temperature value */
} TIDS_Data_t;

/**
 * @struct ITDS_Data_t
 * @brief Represents temperature and acceleration data from the ITDS sensor.
 */
typedef struct ITDS_Data_t {
    ITDS_Temperature_t temperature; /**< Temperature value */
    ITDS_X_t accelX; /**< Acceleration in X-axis */
    ITDS_Y_t accelY; /**< Acceleration in Y-axis */
    ITDS_Z_t accelZ; /**< Acceleration in Z-axis */
} ITDS_Data_t;

/**
 * @struct PADS_Data_t
 * @brief Represents temperature and pressure data from the PADS sensor.
 */
typedef struct PADS_Data_t {
    PADS_Temperature_Float_t temperature_float; /**< Temperature value (float) */
    PADS_Pressure_t pressure; /**< Pressure value */
    PADS_Temperature_Int_t temperature_int; /**< Temperature value (integer) */
} PADS_Data_t;

/**
 * @struct Sensor_Data_t
 * @brief Aggregates sensor data from multiple sources.
 */
typedef struct Sensor_Data_t {
    Device_Id_t _deviceId; /**< Device identifier */
    HIDS_Data_t _Hids; /**< HIDS sensor data */
    TIDS_Data_t _Tids; /**< TIDS sensor data */
    ITDS_Data_t _Itds; /**< ITDS sensor data */
    PADS_Data_t _Pads; /**< PADS sensor data */
} Sensor_Data_t;

/**
 * @brief Converts sensor data to a JSON string.
 * @param paramSensorData Sensor data structure.
 * @return JSON string representation of the sensor data.
 */
extern char* Convert_Sensor_Data_to_JSON(Sensor_Data_t paramSensorData);

/**
 * @brief Converts ITDS sensor data to a JSON string.
 * @param paramSensorData ITDS sensor data structure.
 * @return JSON string representation of the ITDS data.
 */
extern char* Convert_ITDS_to_JSON(Sensor_Data_t paramSensorData);

/**
 * @brief Converts PADS sensor data to a JSON string.
 * @param paramSensorData PADS sensor data structure.
 * @return JSON string representation of the PADS data.
 */
extern char* Convert_PADS_to_JSON(Sensor_Data_t paramSensorData);

/**
 * @brief Converts HIDS sensor data to a JSON string.
 * @param paramSensorData HIDS sensor data structure.
 * @return JSON string representation of the HIDS data.
 */
extern char* Convert_HIDS_to_JSON(Sensor_Data_t paramSensorData);

/**
 * @brief Converts TIDS sensor data to a JSON string.
 * @param paramSensorData TIDS sensor data structure.
 * @return JSON string representation of the TIDS data.
 */
extern char* Convert_TIDS_Data_to_JSON(Sensor_Data_t paramSensorData);

#ifdef __cplusplus
}
#endif

#endif /* SENSOR_DATA_INCLUDE__H_ */
