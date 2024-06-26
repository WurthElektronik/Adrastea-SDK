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

#ifndef AWS_ADRASTEA_H_
#define AWS_ADRASTEA_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "cloud_config.h"
#include "cJSON.h"
#include "cString.h"

/**
 * @brief AWS device certificate file name.
 */
#define AWS_DEVICE_CERTIFICATE_FILE_NAME "ca-certificate.pem.crt"

/**
 * @brief AWS device private key file name.
 */
#define AWS_DEVICE_PRIVATE_KEY_FILE_NAME "ca-private.pem.key"

/**
 * @brief Maximum number of topics AWS can handle.
 */
#define AWS_MAX_TOPICS 4

/**
 * @brief Structure to hold AWS cloud parameters.
 */
typedef struct
{
    char *version;                      /**< Cloud configuration version. */
    char *client_id;                    /**< AWS client ID. */
    char *endpoint_url;                 /**< AWS endpoint URL. */
    char *port_number;                  /**< AWS port number. */
    char *subscribe_topics[AWS_MAX_TOPICS]; /**< Array of subscription topics. */
    char *publish_topic;                /**< Topic to publish messages to. */
    char *keep_alive_time;              /**< Keep-alive time for MQTT connection. */
    char *qos;                          /**< Quality of Service (QoS) level. */
    char *aws_device_cert_file_name;    /**< AWS device certificate file name. */
    char *aws_private_key_file_name;    /**< AWS private key file name. */
    char *aws_device_cert_content;      /**< AWS device certificate content. */
    char *aws_private_key_content;      /**< AWS private key content. */
} AWS_Cloud_Params_t;

/**
 * @brief Reads AWS cloud settings from flash memory.
 *
 * @param[out] p_cloud Pointer to the AWS cloud parameters structure.
 * @param[in]  p_cloud_settings Pointer to the cloud settings structure.
 */
void Read_AWS_Cloud_Settings_From_Flash(AWS_Cloud_Params_t *p_cloud, Cloud_Settings_t *p_cloud_settings);

/**
 * @brief Reads AWS device certificate from flash memory.
 *
 * @param[out] p_cloud Pointer to the AWS cloud parameters structure.
 */
void Read_AWS_Device_Certificate_From_Flash(AWS_Cloud_Params_t *p_cloud);

/**
 * @brief Reads AWS private key from flash memory.
 *
 * @param[out] p_cloud Pointer to the AWS cloud parameters structure.
 */
void Read_AWS_Private_Key_From_Flash(AWS_Cloud_Params_t *p_cloud);

#ifdef __cplusplus
}
#endif

#endif /* AWS_ADRASTEA_H_ */
