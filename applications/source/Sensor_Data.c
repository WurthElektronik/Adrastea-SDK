
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
//  * COPYRIGHT (c) 2025 Würth Elektronik eiSos GmbH & Co. KG
//  *
//  ***************************************************************************************************
//  */


#include "Sensor_Data.h"

/**
 * @brief Replaces double quotes with escaped double quotes in a given JSON string.
 *
 * This function scans through the provided JSON string and replaces each occurrence
 * of a double quote (`"`) with an escaped double quote (`\"`). The result is a new
 * dynamically allocated string that must be freed by the caller.
 *
 * @param string The input JSON string where double quotes need to be escaped.
 *               This parameter should not be NULL.
 *
 * @return A new dynamically allocated string with escaped double quotes.
 *         If memory allocation fails or the input string is NULL, the function returns NULL.
 *
 * @note The caller is responsible for freeing the returned string to avoid memory leaks.
 *
 * @example
 * @code
 * const char *json_string = "{\"key\": \"value with \"quotes\"\"}";
 * char *escaped_string = Add_Escape_Char_to_JSON(json_string);
 * if (escaped_string) {
 *     printf("Escaped JSON string: %s\n", escaped_string);
 *     free(escaped_string);
 * }
 * @endcode
 */
static char *Add_Escape_Char_to_JSON(const char *string)
{
    if (string == NULL)
        return NULL;
    int len = strlen(string);
    int new_len = len * 2;
    char *new_string = (char *)malloc(new_len + 1);

    if (new_string == NULL)
        return NULL;

    char *dest = new_string;

    for (const char *src = string; *src; src++)
    {
        if (*src == '"')
        {
            *dest++ = '\\';
            *dest++ = "\'";
        }
        else
        {
            *dest++ = *src;
        }
    }
    *dest = '\0';

    return new_string;
}


char *Convert_ITDS_to_JSON(Sensor_Data_t paramSensorData)
{
    cJSON *sensor_data_json = cJSON_CreateObject();
    cJSON_AddStringToObject(sensor_data_json, "Device_ID", paramSensorData._deviceId);

    cJSON *ITDS_Node = cJSON_CreateObject();

    cJSON_AddNumberToObject(ITDS_Node, "Temperature", paramSensorData._Itds.temperature);
    cJSON_AddNumberToObject(ITDS_Node, "X", paramSensorData._Itds.accelX);
    cJSON_AddNumberToObject(ITDS_Node, "Y", paramSensorData._Itds.accelY);
    cJSON_AddNumberToObject(ITDS_Node, "Z", paramSensorData._Itds.accelZ);

    cJSON_AddItemToObject(sensor_data_json, "ITDS", ITDS_Node);

    char *string = cJSON_PrintUnformatted(sensor_data_json);

    cJSON_Delete(sensor_data_json);
    char *str = Add_Escape_Char_to_JSON(string);

    return string;
}

char *Convert_PADS_to_JSON(Sensor_Data_t paramSensorData)
{

    cJSON *sensor_data_json = cJSON_CreateObject();
    cJSON_AddStringToObject(sensor_data_json, "Device_ID", paramSensorData._deviceId);

    cJSON *PADS_Node = cJSON_CreateObject();
    cJSON_AddNumberToObject(PADS_Node, "Pressure", paramSensorData._Pads.pressure);
    cJSON_AddNumberToObject(PADS_Node, "Temperature_Float", paramSensorData._Pads.temperature_float);
    cJSON_AddNumberToObject(PADS_Node, "Temperature_Int", paramSensorData._Pads.temperature_int);

    cJSON_AddItemToObject(sensor_data_json, "PADS", PADS_Node);

    char *string = cJSON_PrintUnformatted(sensor_data_json);

    cJSON_Delete(sensor_data_json);
    char *str = Add_Escape_Char_to_JSON(string);

    return string;
}

char *Convert_HIDS_to_JSON(Sensor_Data_t paramSensorData)
{
    cJSON *sensor_data_json = cJSON_CreateObject();
    cJSON_AddStringToObject(sensor_data_json, "Device_ID", paramSensorData._deviceId);

    cJSON *HIDS_Node = cJSON_CreateObject();

    cJSON_AddNumberToObject(HIDS_Node, "Temperature", paramSensorData._Hids.temperature);
    cJSON_AddNumberToObject(HIDS_Node, "Humidity", paramSensorData._Hids.humidity);

    cJSON_AddItemToObject(sensor_data_json, "HIDS", HIDS_Node);

    char *string = cJSON_PrintUnformatted(sensor_data_json);

    cJSON_Delete(sensor_data_json);
    char *str = Add_Escape_Char_to_JSON(string);

    return string;
}

char *Convert_TIDS_Data_to_JSON(Sensor_Data_t paramSensorData)
{
    cJSON *sensor_data_json = cJSON_CreateObject();
    cJSON_AddStringToObject(sensor_data_json, "Device_ID", paramSensorData._deviceId);

    cJSON *TIDS_Node = cJSON_CreateObject();
    cJSON_AddNumberToObject(TIDS_Node, "Temperature", paramSensorData._Tids.temperature);
    cJSON_AddItemToObject(sensor_data_json, "TIDS", TIDS_Node);
    char *string = cJSON_PrintUnformatted(sensor_data_json);

    cJSON_Delete(sensor_data_json);
    char *str = Add_Escape_Char_to_JSON(string);

    return string;
}

char *Convert_Sensor_Data_to_JSON(Sensor_Data_t paramSensorData)
{
    cJSON *sensor_data_json = cJSON_CreateObject();
    char buffer[10];

    cJSON_AddStringToObject(sensor_data_json, "device_ID", paramSensorData._deviceId);
    snprintf(buffer, sizeof(buffer), "%.2f", paramSensorData._Pads.pressure);
    cJSON_AddStringToObject(sensor_data_json, "pressure", buffer );

    snprintf(buffer, sizeof(buffer), "%.2f", paramSensorData._Hids.humidity);
    cJSON_AddStringToObject(sensor_data_json, "humidity", buffer);

    snprintf(buffer, sizeof(buffer), "%.2f", paramSensorData._Itds.temperature);
    cJSON_AddStringToObject(sensor_data_json, "temperature", buffer);

    cJSON *ITDS_Node = cJSON_CreateObject();

    snprintf(buffer, sizeof(buffer), "%.2f", paramSensorData._Itds.accelX);
    cJSON_AddStringToObject(ITDS_Node, "X", buffer);

    snprintf(buffer, sizeof(buffer), "%.2f", paramSensorData._Itds.accelY);
    cJSON_AddStringToObject(ITDS_Node, "Y", buffer);
    
    snprintf(buffer, sizeof(buffer), "%.2f", paramSensorData._Itds.accelZ);
    cJSON_AddStringToObject(ITDS_Node, "Z", buffer);

    cJSON_AddItemToObject(sensor_data_json, "acceleration", ITDS_Node);

    char *string = cJSON_PrintUnformatted(sensor_data_json);

    cJSON_Delete(sensor_data_json);

    char *str = Add_Escape_Char_to_JSON(string);

    return string;
}