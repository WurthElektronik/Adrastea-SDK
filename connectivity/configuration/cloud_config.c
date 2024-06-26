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

#include "cloud_config.h"

void Read_Cloud_Settings_From_Flash(Cloud_Settings_t *p_cloud_settings)
{
    uint32_t cloud_settings[HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE];
    HAL_Flash_Initialize();
    HAL_Flash_Data_Read(HAL_CLOUD_SETTINGS_REGION_START_ADDRESS,
                        cloud_settings,
                        HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE);
    HAL_Flash_Uninitialize();

    int32_t size = sizeof(cloud_settings) / sizeof(cloud_settings[0]);
    char *dest = (char *)malloc(HAL_FLASH_DEFAULT_CUSTOM_SECTION_SIZE * sizeof(char));
    Uint_To_String(cloud_settings, size, dest);

    p_cloud_settings->json_content = malloc(strlen(dest) + 1);
    strcpy(p_cloud_settings->json_content, dest);

    cJSON *json = cJSON_Parse(p_cloud_settings->json_content);

    if (json == NULL)
        return; // If no cloud settings stored inside flash.

    cJSON *version = cJSON_GetObjectItem(json, "version");

    if (cJSON_IsString(version))
    {
        p_cloud_settings->cloud_version = malloc(strlen(version->valuestring) + 1);
        strcpy(p_cloud_settings->cloud_version, version->valuestring);
    }

    cJSON_Delete(json);
    free(dest);
}

Cloud_Type Get_Cloud_Type_From_Version(char *version)
{

    if (strcmp(version, AWS_VERSION) == 0)
    {
        return AWS;
    }
    else if (strcmp(version, AZURE_VERSION) == 0)
    {
        return AZURE;
    }
    else if (strcmp(version, KAAIOT_VERSION) == 0)
    {
        return KAAIOT;
    }
    else if (strcmp(version, MOSQUITTO_VERSION) == 0)
    {
        return MOSQUITTO;
    }
    else if (strcmp(version, MOSQUITTO_TLS_VERSION) == 0)
    {
        return MOSQUITTO_TLS;
    }
    else
    {
        return UNKNOWN_CLOUD_TYPE;
    }
}