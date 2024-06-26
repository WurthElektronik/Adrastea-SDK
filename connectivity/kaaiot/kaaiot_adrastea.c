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

#include "kaaiot_adrastea.h"

void Read_KaaIoT_Cloud_Settings(KaaIoT_Params_t *p_cloud, Cloud_Settings_t *p_cloud_settings)
{
    if (p_cloud_settings->cloud_version != NULL && p_cloud_settings->json_content != NULL)
    {
        cJSON *json = cJSON_Parse(p_cloud_settings->json_content);

        if (json == NULL)
            return; // If no cloud settings stored inside flash.

        cJSON *version = cJSON_GetObjectItem(json, "version");
        cJSON *client_id = cJSON_GetObjectItem(json, "client_id");
        cJSON *endpoint_url = cJSON_GetObjectItem(json, "endpoint_url");
        cJSON *port_number = cJSON_GetObjectItem(json, "port_number");
        cJSON *endpoint_token = cJSON_GetObjectItem(json, "endpoint_token");
        cJSON *application_version = cJSON_GetObjectItem(json, "application_version");
        cJSON *keep_alive_time = cJSON_GetObjectItem(json, "keep_alive_time");
        cJSON *qos = cJSON_GetObjectItem(json, "Qos");

        if (cJSON_IsString(version))
        {
            p_cloud->version = malloc(strlen(version->valuestring) + 1);
            strcpy(p_cloud->version, version->valuestring);
        }

        if (cJSON_IsString(client_id))
        {
            p_cloud->client_id = malloc(strlen(client_id->valuestring) + 1);
            strcpy(p_cloud->client_id, client_id->valuestring);
        }

        if (cJSON_IsString(endpoint_url))
        {
            p_cloud->endpoint_url = malloc(strlen(endpoint_url->valuestring) + 1);
            strcpy(p_cloud->endpoint_url, endpoint_url->valuestring);
        }

        if (cJSON_IsString(port_number))
        {
            p_cloud->port_number = malloc(strlen(port_number->valuestring) + 1);
            strcpy(p_cloud->port_number, port_number->valuestring);
        }

        if (cJSON_IsString(endpoint_token))
        {
            p_cloud->endpoint_token = malloc(strlen(endpoint_token->valuestring) + 1);
            strcpy(p_cloud->endpoint_token, endpoint_token->valuestring);
        }

        if (cJSON_IsString(application_version))
        {
            p_cloud->application_version = malloc(strlen(application_version->valuestring) + 1);
            strcpy(p_cloud->application_version, application_version->valuestring);
        }


        if (cJSON_IsString(keep_alive_time))
        {
            p_cloud->keep_alive_time = malloc(strlen(keep_alive_time->valuestring) + 1);
            strcpy(p_cloud->keep_alive_time, keep_alive_time->valuestring);
        }

        if (cJSON_IsString(qos))
        {
            p_cloud->qos = malloc(strlen(qos->valuestring) + 1);
            strcpy(p_cloud->qos, qos->valuestring);
        }


        int publish_topic_prefix_length = strlen(KAAIOT_PUBLISH_TOPIC_PREFIX);
        int publish_topic_app_version_length = strlen(p_cloud->application_version);
        int publish_topic_extension_instance_length = strlen(KAAIOT_PUBLISH_TOPIC_EXTENSION_INSTANCE_NAME);
        int publish_topic_endpoint_token_length = strlen(p_cloud->endpoint_token);
        int publish_topic_suffix_length = strlen(KAAIOT_PUBLISH_TOPIC_SUFFIX);

        int subscribe_topic_prefix_length = strlen(KAAIOT_SUBSCRIBE_TOPIC_PREFIX);
        int subscribe_topic_app_version_length = strlen(p_cloud->application_version);
        int subscribe_topic_extension_instance_length = strlen(KAAIOT_SUBSCRIBE_TOPIC_EXTENSION_INSTANCE_NAME);
        int subscribe_topic_endpoint_token_length = strlen(p_cloud->endpoint_token);
        int subscribe_topic_suffix_length = strlen(KAAIOT_SUBSCRIBE_TOPIC_SUFFIX);

        p_cloud->publish_topic = malloc(publish_topic_prefix_length + 
                                        publish_topic_app_version_length + 
                                        publish_topic_extension_instance_length + 
                                        publish_topic_endpoint_token_length + 
                                        publish_topic_suffix_length + 1);

        p_cloud->subscribe_topic = malloc(subscribe_topic_prefix_length + 
                                        subscribe_topic_app_version_length + 
                                        subscribe_topic_extension_instance_length + 
                                        subscribe_topic_endpoint_token_length + 
                                        subscribe_topic_suffix_length + 1);
                                        
        strcpy(p_cloud->publish_topic, KAAIOT_PUBLISH_TOPIC_PREFIX);
        strcat(p_cloud->publish_topic, p_cloud->application_version);
        strcat(p_cloud->publish_topic, KAAIOT_PUBLISH_TOPIC_EXTENSION_INSTANCE_NAME);
        strcat(p_cloud->publish_topic, p_cloud->endpoint_token);
        strcat(p_cloud->publish_topic, KAAIOT_PUBLISH_TOPIC_SUFFIX);

        strcpy(p_cloud->subscribe_topic, KAAIOT_SUBSCRIBE_TOPIC_PREFIX);
        strcat(p_cloud->subscribe_topic, p_cloud->application_version);
        strcat(p_cloud->subscribe_topic, KAAIOT_SUBSCRIBE_TOPIC_EXTENSION_INSTANCE_NAME);
        strcat(p_cloud->subscribe_topic, p_cloud->endpoint_token);
        strcat(p_cloud->subscribe_topic, KAAIOT_SUBSCRIBE_TOPIC_SUFFIX);

        cJSON_Delete(json);
    }
}