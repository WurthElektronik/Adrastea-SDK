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


#ifndef MOSQUITTO_ADRASTEA_H_
#define MOSQUITTO_ADRASTEA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"
#include "cloud_config.h"
#include "cJSON.h"
#include "cString.h"

/**
 * @brief Mosquitto client certificate file name.
 */
#define MOSQUITTO_CERTIFICATE_FILE_NAME "client.crt"

/**
 * @brief Mosquitto client private key file name.
 */
#define MOSQUITTO_PRIVATE_KEY_FILE_NAME "client.key"

/**
 * @brief Mosquitto root CA certificate file name.
 */
#define MOSQUITTO_ROOT_FILE_NAME "mosquitto.org.crt"

/**
 * @brief Maximum number of MQTT topics.
 */
#define MOSQUITTO_MAX_TOPICS 4

/**
 * @brief Structure to hold Mosquitto MQTT client parameters.
 */
typedef struct
{
    char *version;                              /**< MQTT version. */
    char *client_id;                            /**< Client identifier. */
    char *endpoint_url;                         /**< MQTT broker URL. */
    char *port_number;                          /**< Port number for MQTT connection. */
    char *subscribe_topics[MOSQUITTO_MAX_TOPICS]; /**< Topics to subscribe to. */
    char *publish_topic;                        /**< Topic to publish messages to. */
    char *keep_alive_time;                      /**< Keep-alive interval in seconds. */
    char *qos;                                  /**< Quality of Service level. */
} Mosquitto_Params_t;

/**
 * @brief Structure to hold Mosquitto certificate data.
 */
typedef struct
{
    char *client_cert_content;           /**< Client certificate content. */
    char *client_cert_file_name;         /**< Client certificate file name. */
    char *client_key_content;            /**< Client private key content. */
    char *client_key_file_name;          /**< Client private key file name. */
    char *mosquitto_root_cert_content;   /**< Root CA certificate content. */
    char *mosquitto_root_cert_file_name; /**< Root CA certificate file name. */
} Mosquitto_Certificates_t;

/**
 * @brief Reads Mosquitto cloud settings from a configuration structure.
 *
 * @param[out] p_cloud Pointer to the structure to store cloud settings.
 * @param[in]  p_cloud_settings Pointer to the cloud configuration settings.
 */
void Read_Mosquitto_Cloud_Settings(Mosquitto_Params_t *p_cloud, Cloud_Settings_t *p_cloud_settings);

/**
 * @brief Reads the Mosquitto client certificate from flash storage.
 *
 * @param[out] p_cloud_cert Pointer to the structure to store certificate data.
 */
void Read_Mosquitto_Client_Certificate_From_Flash(Mosquitto_Certificates_t *p_cloud_cert);

/**
 * @brief Reads the Mosquitto client private key from flash storage.
 *
 * @param[out] p_cloud_cert Pointer to the structure to store key data.
 */
void Read_Mosquitto_Client_Key_From_Flash(Mosquitto_Certificates_t *p_cloud_cert);

/**
 * @brief Reads the Mosquitto root CA certificate from flash storage.
 *
 * @param[out] p_cloud_cert Pointer to the structure to store root certificate data.
 */
void Read_Mosquitto_Root_Cert_From_Flash(Mosquitto_Certificates_t *p_cloud_cert);

#ifdef __cplusplus
}
#endif

#endif /* MOSQUITTO_ADRASTEA_H_ */