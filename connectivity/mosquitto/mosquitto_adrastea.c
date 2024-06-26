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

#include "mosquitto_adrastea.h"

void Read_Mosquitto_Cloud_Settings(Mosquitto_Params_t *p_cloud, Cloud_Settings_t *p_cloud_settings)
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

        if (cJSON_IsString(publish_topic))
        {
            p_cloud->publish_topic = malloc(strlen(publish_topic->valuestring) + 1);
            strcpy(p_cloud->publish_topic, publish_topic->valuestring);
        }

        if (cJSON_IsArray(subscribe_topics))
        {
            int count = cJSON_GetArraySize(subscribe_topics);
            // the topic buffer limited to KAAIOT_MAX_TOPIC
            if (count > MOSQUITTO_MAX_TOPICS)
                count = MOSQUITTO_MAX_TOPICS;

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

        cJSON_Delete(json);
    }
}

void Read_Mosquitto_Client_Certificate_From_Flash(Mosquitto_Certificates_t *p_cloud_cert)
{
    uint32_t mosquitto_client_cert[HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE];
    HAL_Flash_Initialize();
    HAL_Flash_Data_Read(HAL_DEVICE_CERTIFICATE_REGION_START_ADDRESS, mosquitto_client_cert, HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE);
    HAL_Flash_Uninitialize();

    if (mosquitto_client_cert != NULL)
    {
        int32_t size = sizeof(mosquitto_client_cert) / sizeof(mosquitto_client_cert[0]);
        char *dest = (char *)malloc(HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE * sizeof(char));
        Uint_To_String(mosquitto_client_cert, size, dest);
        p_cloud_cert->client_cert_content = malloc(strlen(dest) + 1);
        strcpy(p_cloud_cert->client_cert_content, dest);
        free(dest);

        p_cloud_cert->client_cert_file_name = malloc(strlen(MOSQUITTO_CERTIFICATE_FILE_NAME) + 1);
        strcpy(p_cloud_cert->client_cert_file_name, MOSQUITTO_CERTIFICATE_FILE_NAME);
    }
}

void Read_Mosquitto_Client_Key_From_Flash(Mosquitto_Certificates_t *p_cloud_cert)
{
    uint32_t mosquitto_client_key[HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE];
    HAL_Flash_Initialize();
    HAL_Flash_Data_Read(HAL_PRIVATE_KEY_REGION_START_ADDRESS, mosquitto_client_key, HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE);
    HAL_Flash_Uninitialize();

    if (mosquitto_client_key != NULL)
    {
        int32_t size = sizeof(mosquitto_client_key) / sizeof(mosquitto_client_key[0]);
        char *dest = (char *)malloc(HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE * sizeof(char));
        Uint_To_String(mosquitto_client_key, size, dest);
        p_cloud_cert->client_key_content = malloc(strlen(dest) + 1);
        strcpy(p_cloud_cert->client_key_content, dest);
        free(dest);

        p_cloud_cert->client_key_file_name = malloc(strlen(MOSQUITTO_PRIVATE_KEY_FILE_NAME) + 1);
        strcpy(p_cloud_cert->client_key_file_name, MOSQUITTO_PRIVATE_KEY_FILE_NAME);
    }
}

void Read_Mosquitto_Root_Cert_From_Flash(Mosquitto_Certificates_t *p_cloud_cert)
{
    uint32_t mosquitto_root_cert[HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE];
    HAL_Flash_Initialize();
    HAL_Flash_Data_Read(HAL_ROOT_CERT_REGION_START_ADDRESS, mosquitto_root_cert, HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE);
    HAL_Flash_Uninitialize();

    if (mosquitto_root_cert != NULL)
    {
        int32_t size = sizeof(mosquitto_root_cert) / sizeof(mosquitto_root_cert[0]);
        char *dest = (char *)malloc(HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE * sizeof(char));
        Uint_To_String(mosquitto_root_cert, size, dest);
        p_cloud_cert->mosquitto_root_cert_content = malloc(strlen(dest) + 1);
        strcpy(p_cloud_cert->mosquitto_root_cert_content, dest);
        free(dest);

        p_cloud_cert->mosquitto_root_cert_file_name = malloc(strlen(MOSQUITTO_ROOT_FILE_NAME) + 1);
        strcpy(p_cloud_cert->mosquitto_root_cert_file_name, MOSQUITTO_ROOT_FILE_NAME);
    }
}
