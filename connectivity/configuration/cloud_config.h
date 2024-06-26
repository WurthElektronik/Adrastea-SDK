
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

#ifndef CLOUD_CONFIG_H_
#define CLOUD_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "cJSON.h"
#include "cString.h"

#define AWS_VERSION             "1.0"
#define AZURE_VERSION           "2.0"
#define KAAIOT_VERSION          "3.0"
#define MOSQUITTO_VERSION       "5.0"
#define MOSQUITTO_TLS_VERSION   "6.0"

#define PUBLISH_FREQ 60000 /*How often the data will be published to target cloud*/

/**
 * @enum Cloud_Type
 * @brief Enumeration of cloud service types.
 *
 * This enumeration defines the various cloud service types supported.
 * It is used to specify the cloud platform in use.
 */
typedef enum
{
    /**
     * @brief Amazon Web Services.
     * @details Corresponds to version 1.0.
     */
    AWS = 1,

    /**
     * @brief Microsoft Azure.
     * @details Corresponds to version 2.0.
     */
    AZURE = 2,

    /**
     * @brief Kaa IoT platform without TLS.
     * @details Corresponds to version 3.0.
     */
    KAAIOT = 3,


    /**
     * @brief Mosquitto MQTT broker without TLS.
     * @details Corresponds to version 5.0.
     */
    MOSQUITTO = 5,

    /**
     * @brief Mosquitto MQTT broker with TLS.
     * @details Corresponds to version 6.0.
     */
    MOSQUITTO_TLS = 6,

    /**
     * @brief Unsupported cloud type.
     * @details Used as a fallback for unknown or unsupported cloud platforms.
     */
    UNKNOWN_CLOUD_TYPE
} Cloud_Type;



    /**
     * @brief Structure to store cloud settings.
     *
     * This structure holds the JSON content for cloud configuration.
     */
    typedef struct
    {
        char *cloud_version;
        char *json_content;

    } Cloud_Settings_t;

    /**
     * @brief Reads cloud settings from flash memory.
     *
     * This function reads the cloud settings stored in flash memory and
     * populates the provided Cloud_Settings_t structure with the JSON content.
     *
     * @param[out] cloud_settings Pointer to a Cloud_Settings_t structure that
     *                            will be filled with the JSON content from flash.
     */
    extern void Read_Cloud_Settings_From_Flash(Cloud_Settings_t *p_cloud_settings);

    /**
     * @brief Determines the Cloud_Type based on the provided version string.
     *
     * This function takes a version string as input and maps it to the corresponding
     * Cloud_Type enum value. If the version is not recognized, it returns UNKNOWN_VERSION.
     *
     * @param version Pointer to a string representing the version (e.g., "1.0").
     *                The string should be null-terminated.
     *
     * @return Cloud_Type Enum value corresponding to the version.
     *         If the version is unrecognized, returns UNKNOWN_VERSION.
     */
    extern Cloud_Type Get_Cloud_Type_From_Version(char *version);

#ifdef __cplusplus
}
#endif

#endif /* CLOUD_CONFIG_H_ */
