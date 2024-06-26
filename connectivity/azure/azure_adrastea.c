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

#include "azure_adrastea.h"

void Read_Azure_Cloud_Settings_From_Flash(Azure_Params_t *p_cloud, Cloud_Settings_t *p_cloud_settings)
{
    if (p_cloud_settings->cloud_version != NULL && p_cloud_settings->json_content != NULL)
    {
        cJSON *json = cJSON_Parse(p_cloud_settings->json_content);

        if (json == NULL)
            return; // If no cloud settings stored inside flash.

        cJSON *version = cJSON_GetObjectItem(json, "version");           // ok
        cJSON *device_id = cJSON_GetObjectItem(json, "device_id");       // ok
        cJSON *iot_hub_name = cJSON_GetObjectItem(json, "iot_hub_name"); // ok
        cJSON *api_version = cJSON_GetObjectItem(json, "api_version");   // ok
        cJSON *port_number = cJSON_GetObjectItem(json, "port_number");   // ok
        cJSON *keep_alive_time = cJSON_GetObjectItem(json, "keep_alive_time");
        cJSON *qos = cJSON_GetObjectItem(json, "Qos");

        if (cJSON_IsString(version))
        {
            p_cloud->version = malloc(strlen(version->valuestring) + 1);
            strcpy(p_cloud->version, version->valuestring);
        }

        if (cJSON_IsString(device_id))
        {
            p_cloud->device_id = malloc(strlen(device_id->valuestring) + 1);
            p_cloud->client_id = malloc(strlen(device_id->valuestring) + 1);
            strcpy(p_cloud->device_id, device_id->valuestring);
            strcpy(p_cloud->client_id, device_id->valuestring); //Set clientID with DeviceID
        }

        if (cJSON_IsString(iot_hub_name))
        {
            p_cloud->iot_hub_name = malloc(strlen(iot_hub_name->valuestring) + 1);
            strcpy(p_cloud->iot_hub_name, iot_hub_name->valuestring);
        }

        if (cJSON_IsString(api_version))
        {
            p_cloud->api_version = malloc(strlen(api_version->valuestring) + 1);
            strcpy(p_cloud->api_version, api_version->valuestring);
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

        // Build up subscribe topic for azure

          int device_id_length = strlen(p_cloud->device_id);

        int subscribe_topic_prefix_length = strlen(AZURE_TOPIC_PREFIX);
        int subscribe_topic_suffix_length = strlen(AZURE_SUBSCRIBE_TOPIC_SUFFIX);

        p_cloud->subscribe_topic = malloc(subscribe_topic_prefix_length + device_id_length + subscribe_topic_suffix_length + 1);
        strcpy(p_cloud->subscribe_topic, AZURE_TOPIC_PREFIX);
        strcat(p_cloud->subscribe_topic, "/");
        strcat(p_cloud->subscribe_topic, p_cloud->device_id);
        strcat(p_cloud->subscribe_topic, AZURE_SUBSCRIBE_TOPIC_SUFFIX);

        // Build up publish topic for azure
        int publish_topic_prefix_length = strlen(AZURE_TOPIC_PREFIX);
        int publish_topic_suffix_length = strlen(AZURE_PUBLISH_TOPIC_SUFFIX);

        p_cloud->publish_topic = malloc(publish_topic_prefix_length + device_id_length + publish_topic_suffix_length + 1);
        strcpy(p_cloud->publish_topic, AZURE_TOPIC_PREFIX);
        strcat(p_cloud->publish_topic, "/");
        strcat(p_cloud->publish_topic, p_cloud->device_id);
        strcat(p_cloud->publish_topic, AZURE_PUBLISH_TOPIC_SUFFIX);

        // Build up user_name

        int user_name_prefix_length = strlen(p_cloud->iot_hub_name);
        int end_point_length = strlen(AZURE_ENDPOINT_SUFFIX);
        int api_version_prefix_length = strlen(AZURE_API_VERSION_SUFFIX);
        int api_version_length = strlen(p_cloud->api_version);

        p_cloud->user_name = malloc(user_name_prefix_length + end_point_length + device_id_length + api_version_prefix_length + api_version_length + 1);
        strcpy(p_cloud->user_name, p_cloud->iot_hub_name);
        strcat(p_cloud->user_name, AZURE_ENDPOINT_SUFFIX);
        strcat(p_cloud->user_name, "/");
        strcat(p_cloud->user_name, p_cloud->device_id);
        strcat(p_cloud->user_name, AZURE_API_VERSION_SUFFIX);
        strcat(p_cloud->user_name, p_cloud->api_version);

        // Build up endpoint_url
        p_cloud->endpoint_url = malloc(user_name_prefix_length + strlen(AZURE_ENDPOINT_SUFFIX) + 1);
        strcpy(p_cloud->endpoint_url, p_cloud->iot_hub_name);
        strcat(p_cloud->endpoint_url, AZURE_ENDPOINT_SUFFIX);

        cJSON_Delete(json);
    }
}

void Read_Azure_Device_Certificate_From_Flash(Azure_Params_t *p_cloud)
{

    uint32_t azure_device_cert[HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE];
    HAL_Flash_Initialize();
    HAL_Flash_Data_Read(HAL_DEVICE_CERTIFICATE_REGION_START_ADDRESS, azure_device_cert, HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE);
    HAL_Flash_Uninitialize();

    if (azure_device_cert != NULL)
    {
        int32_t size = sizeof(azure_device_cert) / sizeof(azure_device_cert[0]);
        char *dest = (char *)malloc(HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE * sizeof(char));
        Uint_To_String(azure_device_cert, size, dest);
        p_cloud->azure_device_cert_content = malloc(strlen(dest) + 1);
        strcpy(p_cloud->azure_device_cert_content, dest);
        free(dest);

        p_cloud->azure_device_cert_file_name = malloc(strlen(AZURE_DEVICE_CERTIFICATE_FILE_NAME) + 1);
        strcpy(p_cloud->azure_device_cert_file_name, AZURE_DEVICE_CERTIFICATE_FILE_NAME);
    }
}

void Read_Azure_Private_Key_From_Flash(Azure_Params_t *p_cloud)
{
    uint32_t azure_private_key[HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE];
    HAL_Flash_Initialize();
    HAL_Flash_Data_Read(HAL_PRIVATE_KEY_REGION_START_ADDRESS, azure_private_key, HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE);
    HAL_Flash_Uninitialize();

    if (azure_private_key != NULL)
    {
        int32_t size = sizeof(azure_private_key) / sizeof(azure_private_key[0]);
        char *dest = (char *)malloc(HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE * sizeof(char));
        Uint_To_String(azure_private_key, size, dest);
        p_cloud->azure_private_key_content = malloc(strlen(dest) + 1);
        strcpy(p_cloud->azure_private_key_content, dest);
        free(dest);

        p_cloud->azure_private_key_file_name = malloc(strlen(AZURE_DEVICE_PRIVATE_KEY_FILE_NAME) + 1);
        strcpy(p_cloud->azure_private_key_file_name, AZURE_DEVICE_PRIVATE_KEY_FILE_NAME);
    }
}

void Read_Azure_Root_Cert_From_Flash(Azure_Params_t *p_cloud)
{
    uint32_t azure_root_cert[HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE];
    HAL_Flash_Initialize();
    HAL_Flash_Data_Read(HAL_ROOT_CERT_REGION_START_ADDRESS, azure_root_cert, HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE);
    HAL_Flash_Uninitialize();

    if (azure_root_cert != NULL)
    {
        int32_t size = sizeof(azure_root_cert) / sizeof(azure_root_cert[0]);
        char *dest = (char *)malloc(HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE * sizeof(char));
        Uint_To_String(azure_root_cert, size, dest);
        p_cloud->azure_root_cert_content = malloc(strlen(dest) + 1);
        strcpy(p_cloud->azure_root_cert_content, dest);
        free(dest);

        p_cloud->azure_root_cert_file_name = malloc(strlen(AZURE_DEVICE_ROOT_FILE_NAME) + 1);
        strcpy(p_cloud->azure_root_cert_file_name, AZURE_DEVICE_ROOT_FILE_NAME);
    }
}
