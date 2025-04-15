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

#include "aws_adrastea.h"

void Read_AWS_Cloud_Settings_From_Flash(AWS_Cloud_Params_t *p_cloud, Cloud_Settings_t *p_cloud_settings)
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
        cJSON *subscribe_topics = cJSON_GetObjectItem(json, "subscribe_topics");
        cJSON *publish_topic = cJSON_GetObjectItem(json, "publish_topic");
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

        if (cJSON_IsString(version))
        {
            p_cloud->version = malloc(strlen(version->valuestring) + 1);
            strcpy(p_cloud->version, version->valuestring);
        }

        if (cJSON_IsArray(subscribe_topics))
        {
            int count = cJSON_GetArraySize(subscribe_topics);
            // the topic buffer limited to MAX_TOPICS
            if (count > AWS_MAX_TOPICS)
                count = AWS_MAX_TOPICS;

            for (int i = 0; i < count; i++)
            {
                cJSON *topic = cJSON_GetArrayItem(subscribe_topics, i);
                if (cJSON_IsString(topic))
                {
                    p_cloud->subscribe_topics[i] = malloc(strlen(topic->valuestring) + 1);
                    strcpy(p_cloud->subscribe_topics[i], topic->valuestring);
                }
            }
        }

        if (cJSON_IsString(publish_topic))
        {
            p_cloud->publish_topic = malloc(strlen(publish_topic->valuestring) + 1);
            strcpy(p_cloud->publish_topic, publish_topic->valuestring);
        }

        cJSON_Delete(json);
    }
}

void Read_AWS_Device_Certificate_From_Flash(AWS_Cloud_Params_t *p_cloud)
{

    uint32_t aws_device_cert[HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE];
    HAL_Flash_Initialize();
    HAL_Flash_Data_Read(HAL_DEVICE_CERTIFICATE_REGION_START_ADDRESS, aws_device_cert, HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE);
    HAL_Flash_Uninitialize();

    if (aws_device_cert != NULL)
    {

        int32_t size = sizeof(aws_device_cert) / sizeof(aws_device_cert[0]);
        char *dest = (char *)malloc(HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE * sizeof(char));
        Uint_To_String(aws_device_cert, size, dest);
        p_cloud->aws_device_cert_content = malloc(strlen(dest) + 1);
        strcpy(p_cloud->aws_device_cert_content, dest);
        free(dest);

        p_cloud->aws_device_cert_file_name = malloc(strlen(AWS_DEVICE_CERTIFICATE_FILE_NAME) + 1);
        strcpy(p_cloud->aws_device_cert_file_name, AWS_DEVICE_CERTIFICATE_FILE_NAME);
    }
}

void Read_AWS_Private_Key_From_Flash(AWS_Cloud_Params_t *p_cloud)
{

    uint32_t aws_private_key[HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE];
    HAL_Flash_Initialize();
    HAL_Flash_Data_Read(HAL_PRIVATE_KEY_REGION_START_ADDRESS, aws_private_key, HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE);
    HAL_Flash_Uninitialize();

    if (aws_private_key != NULL)
    {
        int32_t size = sizeof(aws_private_key) / sizeof(aws_private_key[0]);
        char *dest = (char *)malloc(HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE * sizeof(char));
        Uint_To_String(aws_private_key, size, dest);
        p_cloud->aws_private_key_content = malloc(strlen(dest) + 1);
        strcpy(p_cloud->aws_private_key_content, dest);
        free(dest);

        p_cloud->aws_private_key_file_name = malloc(strlen(AWS_DEVICE_PRIVATE_KEY_FILE_NAME) + 1);
        strcpy(p_cloud->aws_private_key_file_name, AWS_DEVICE_PRIVATE_KEY_FILE_NAME);
    }
}
