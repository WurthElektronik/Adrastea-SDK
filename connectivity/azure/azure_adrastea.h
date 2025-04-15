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
#ifndef AZURE_ADRASTEA_H_
#define AZURE_ADRASTEA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"
#include "cloud_config.h"
#include "cJSON.h"
#include "cString.h"

/**
 * @brief Azure device certificate file name.
 */
#define AZURE_DEVICE_CERTIFICATE_FILE_NAME "azdevcert2.pem.crt"

/**
 * @brief Azure device private key file name.
 */
#define AZURE_DEVICE_PRIVATE_KEY_FILE_NAME "azdevkey2.pem.key"

/**
 * @brief Azure root certificate file name.
 */
#define AZURE_DEVICE_ROOT_FILE_NAME "azrootca2.pem"

/**
 * @brief Maximum number of topics supported.
 */
#define AZURE_MAX_TOPICS 1

/**
 * @brief Azure-specific topic and endpoint suffixes.
 */
#define AZURE_ENDPOINT_SUFFIX ".azure-devices.net"
#define AZURE_API_VERSION_SUFFIX "/?api-version="
#define AZURE_SUBSCRIBE_TOPIC_SUFFIX "/messages/devicebound/#"
#define AZURE_PUBLISH_TOPIC_SUFFIX "/messages/events/"
#define AZURE_TOPIC_PREFIX "devices"

/**
 * @brief Structure to hold Azure cloud parameters.
 */
typedef struct
{
    char *version;                         /**< Azure connection version. */
    char *client_id;                       /**< Client identifier. */
    char *device_id;                       /**< Azure device ID. */
    char *user_name;                       /**< Username for authentication. */
    char *endpoint_url;                    /**< Azure cloud endpoint URL. */
    char *port_number;                     /**< Port number for connection. */
    char *subscribe_topic;                 /**< MQTT topic to subscribe to. */
    char *publish_topic;                   /**< MQTT topic to publish to. */
    char *keep_alive_time;                 /**< Keep-alive interval in seconds. */
    char *iot_hub_name;                    /**< IoT Hub name. */
    char *api_version;                     /**< Azure API version. */
    char *qos;                             /**< Quality of Service level. */
    char *azure_device_cert_file_name;     /**< Path to device certificate file. */
    char *azure_private_key_file_name;     /**< Path to private key file. */
    char *azure_root_cert_file_name;       /**< Path to root certificate file. */
    char *azure_device_cert_content;       /**< Device certificate content. */
    char *azure_private_key_content;       /**< Private key content. */
    char *azure_root_cert_content;         /**< Root certificate content. */
} Azure_Params_t;

/**
 * @brief Reads Azure cloud settings from flash memory.
 *
 * @param[out] p_cloud Structure to store the retrieved cloud settings.
 * @param[in]  p_cloud_settings Structure containing stored cloud settings.
 */
void Read_Azure_Cloud_Settings_From_Flash(Azure_Params_t *p_cloud, Cloud_Settings_t* p_cloud_settings);

/**
 * @brief Reads Azure device certificate from flash memory.
 *
 * @param[out] p_cloud Structure to store the retrieved certificate content.
 */
void Read_Azure_Device_Certificate_From_Flash(Azure_Params_t *p_cloud);

/**
 * @brief Reads Azure private key from flash memory.
 *
 * @param[out] p_cloud Structure to store the retrieved private key content.
 */
void Read_Azure_Private_Key_From_Flash(Azure_Params_t *p_cloud);

/**
 * @brief Reads Azure root certificate from flash memory.
 *
 * @param[out] p_cloud Structure to store the retrieved root certificate content.
 */
void Read_Azure_Root_Cert_From_Flash(Azure_Params_t *p_cloud);

#ifdef __cplusplus
}
#endif

#endif /* AZURE_ADRASTEA_H_ */