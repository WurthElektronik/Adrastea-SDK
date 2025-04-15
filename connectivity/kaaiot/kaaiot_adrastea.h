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

#ifndef KAAIOT_ADRASTEA_H_
#define KAAIOT_ADRASTEA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"
#include "cloud_config.h"
#include "cJSON.h"
#include "cString.h"

/**
 * @brief Root certificate file name for KaaIoT cloud.
 */
#define KAAIOT_ROOT_FILE_NAME "ca.pem"

/**
 * @name KaaIoT MQTT Topic Components
 * @{
 */
#define KAAIOT_PUBLISH_TOPIC_PREFIX "kp1/"
#define KAAIOT_PUBLISH_TOPIC_EXTENSION_INSTANCE_NAME "/dcx/"
#define KAAIOT_PUBLISH_TOPIC_SUFFIX "/json"

#define KAAIOT_SUBSCRIBE_TOPIC_PREFIX "kp1/"
#define KAAIOT_SUBSCRIBE_TOPIC_EXTENSION_INSTANCE_NAME "/dcx/"
#define KAAIOT_SUBSCRIBE_TOPIC_SUFFIX "/json"
/** @} */

/**
 * @brief Structure to hold KaaIoT cloud parameters.
 */
typedef struct
{
    char *version;                /**< Cloud API version. */
    char *client_id;              /**< Client identifier. */
    char *endpoint_url;           /**< Endpoint URL. */
    char *port_number;            /**< Port number for the connection. */
    char *subscribe_topic;        /**< Topic to subscribe to. */
    char *publish_topic;          /**< Topic to publish to. */
    char *endpoint_token;         /**< Endpoint token for authorization. */
    char *application_version;    /**< Version of the cloud application. */
    char *keep_alive_time;        /**< Keep-alive time interval in seconds. */
    char *qos;                    /**< Quality of Service level. */
} KaaIoT_Params_t;

/**
 * @brief Structure to hold KaaIoT certificate information.
 */
typedef struct
{
    char *kaaiot_root_cert_file_name;     /**< Root certificate file name. */
    char *kaaiot_root_cert_file_content;  /**< Root certificate file content. */
} KaaIoT_Certificates_t;

/**
 * @brief Reads KaaIoT cloud settings from a configuration structure.
 *
 * @param[out] p_cloud Pointer to the KaaIoT parameters structure.
 * @param[in]  p_cloud_settings Pointer to the cloud settings structure.
 */
void Read_KaaIoT_Cloud_Settings(KaaIoT_Params_t *p_cloud, Cloud_Settings_t *p_cloud_settings);

#ifdef __cplusplus
}
#endif

#endif /* KAAIOT_ADRASTEA_H_ */