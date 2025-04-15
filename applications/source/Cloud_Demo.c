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


#include "hal_common.h"
#include "Sensor_App.h"
#include "Sensor_Data.h"

/* Cloud Types Connectivity */
#include "cloud_config.h"
#include "aws_adrastea.h"
#include "azure_adrastea.h"
#include "kaaiot_adrastea.h"
#include "mosquitto_adrastea.h"

Sensor_Data_t data;
char *payload;
char *payload_formatted;

/* State Machine */
typedef enum
{
    Adrastea_Application_SM_Read_Cloud_Parameters,
    Adrastea_Application_SM_PinRegistered,
    Adrastea_Application_SM_SetNetworkState,
    Adrastea_Application_SM_Wait4NetworkRegistered,
    Adrastea_Application_SM_CheckPingStatus,
    Adrastea_Application_SM_ReadCloudConfiguration,
    Adrastea_Application_SM_AWSMQTT_Connect,
    Adrastea_Application_SM_AWSMQTT_Subscribe,
    Adrastea_Application_SM_AWSMQTT_PublishData,
    Adrastea_Application_SM_Azure_Connect,
    Adrastea_Application_SM_Azure_Subscribe,
    Adrastea_Application_SM_Azure_PublishData,
    Adrastea_Application_SM_KaaIOT_Connect,
    Adrastea_Application_SM_KaaIOT_Subscribe,
    Adrastea_Application_SM_KaaIOT_PublishData,
    Adrastea_Application_SM_Mosquitto_Connect,
    Adrastea_Application_SM_Mosquitto_Connect_TLS,
    Adrastea_Application_SM_Mosquitto_Subscribe,
    Adrastea_Application_SM_Mosquitto_PublishData,
    Adrastea_Application_SM_Mosquitto_TLS_Subscribe,
    Adrastea_Application_SM_Mosquitto_TLS_PublishData,
    Adrastea_Application_SM_Idle,
    Adrastea_Application_SM_Error,
    Adrastea_Application_SM_Ready,
    Adrastea_Application_SM_Ready_AWS,
    Adrastea_Application_SM_Ready_Azure,
    Adrastea_Application_SM_Ready_KaaIoT,
    Adrastea_Application_SM_Ready_Mosquitto,
    Adrastea_Application_SM_Ready_Mosquitto_TLS,
    Adrastea_Application_SM_Network_Dropped

} Adrastea_Application_SM_t;

static volatile Adrastea_Application_SM_t adrasteaApplicationCurrentState = Adrastea_Application_SM_Idle;
static volatile ATPacketDomain_Network_Registration_Status_t status;
static volatile ATPacketDomain_Network_Registration_Status_t networkRegistrationStatus;

static volatile Cloud_Type cloud_type;
static volatile int size_of_payload;

volatile bool pingOk;
volatile bool isSubscribed;
volatile bool isConnected;
volatile bool isNetworkInitialized ;

ATSIM_PIN_Status_t pinStatus = ATSIM_PIN_Status_Invalid;
ATDevice_IMEI_t imei_p;
Adrastea_Pins_t Adrastea_pins;

Cloud_Settings_t p_cloud_settings;
AWS_Cloud_Params_t p_cloud_aws;
Azure_Params_t p_cloud_azure;
Mosquitto_Params_t p_cloud_mosquitto;
KaaIoT_Params_t p_cloud_kaaiot;
Mosquitto_Certificates_t p_cloud_mosquitto_cert;
KaaIoT_Certificates_t p_cloud_kaaiot_cert;
TaskHandle_t Device_Task = NULL;
TaskHandle_t Sensor_Task = NULL;

void Init__Cloud__Task();
void Adrastea_EventCallback(char *eventText);
void Init__Cloud()
{

    xTaskCreate(Init__Cloud__Task,            /* The function that implements the task. */
                "Init__Cloud__Task",          /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                configMINIMAL_STACK_SIZE * 2, /* The size of the stack to allocate to the task. */
                (void *)NULL,                 /* The parameter passed to the task */
                configMAX_PRIORITIES - 1,     /* The priority assigned to the task - minimal priority. */
                &Device_Task);

    return WE_SUCCESS;
}

void Adrastea_EventCallback(char *eventText)
{
    ATEvent_t event;
    ATEvent_ParseEventType(&eventText, &event);
    char eventName[32];
    ATEvent_GetEventName(event, eventName);

    WE_Delay(200);
    switch (event)
    {

        /**************************************************************************************/

    case ATEvent_MQTT_AWSIOT_Connection_Confirmation:
    {
        ATMQTT_Event_Result_Code_t connResultAws;

        ATMQTT_ParseAWSIOTConnectionConfirmationEvent(eventText, &connResultAws);

        if (connResultAws == ATMQTT_Event_Result_Code_Fail)
        {
            printf("AWS Connection failed \r\n");
            adrasteaApplicationCurrentState = Adrastea_Application_SM_AWSMQTT_Connect;
        }
        else if (connResultAws == ATMQTT_Event_Result_Code_Success)
        {
            printf("INFO : AWS  Connection successfull !  \r\n");
            adrasteaApplicationCurrentState = Adrastea_Application_SM_AWSMQTT_Subscribe;
        }
        break;
    }

    case ATEvent_MQTT_AWSIOT_Subscription_Confirmation:
    {
        ATMQTT_AWSIOT_Subscription_Result_t subResultAws;
        ATMQTT_ParseAWSIOTSubscriptionConfirmationEvent(eventText, &subResultAws);

        if (subResultAws.resultCode == ATMQTT_Event_Result_Code_Fail)
        {
            adrasteaApplicationCurrentState = Adrastea_Application_SM_AWSMQTT_Subscribe;
        }
        else
        {
            adrasteaApplicationCurrentState = Adrastea_Application_SM_Ready_AWS;
        }
        break;
    }
    /*******************************************************************************************/
    case ATEvent_MQTT_Connection_Failure:
    {

        switch (cloud_type)
        {
        case MOSQUITTO:
            adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_Connect;
            break;
        case MOSQUITTO_TLS:
            adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_Connect_TLS;
            break;
        case KAAIOT:
            adrasteaApplicationCurrentState = Adrastea_Application_SM_KaaIOT_Connect;
            break;
        case AZURE:
            adrasteaApplicationCurrentState = Adrastea_Application_SM_Azure_Connect;
            break;
        }

        break;
    }

    case ATEvent_MQTT_Connection_Confirmation:
    {
        ATMQTT_Connection_Result_t connResult;

        switch (cloud_type)
        {
        case MOSQUITTO:
            if (!ATMQTT_ParseConnectionConfirmationEvent(eventText, &connResult))
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_Connect;
            }
            else if (connResult.resultCode == ATMQTT_Event_Result_Code_Success)
            {
                printf(" INFO : MQTT Mosquitto Connection successfull !  \r\n");
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_Subscribe;
            }
            break;
        case MOSQUITTO_TLS:

            if (!ATMQTT_ParseConnectionConfirmationEvent(eventText,
                                                         &connResult))
            {

                adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_Connect_TLS;
            }
            else if (connResult.resultCode == ATMQTT_Event_Result_Code_Success)
            {

                printf("INFO : MQTT Mosquitto_TLS Connection successfull !  \r\n");
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_TLS_Subscribe;
            }
            break;
        case KAAIOT:
            if (!ATMQTT_ParseConnectionConfirmationEvent(eventText,
                                                         &connResult))
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_KaaIOT_Connect;
            }
            else if (connResult.resultCode == ATMQTT_Event_Result_Code_Success)
            {
                printf("INFO : KaaIoT Connection successfull !  \r\n");
                adrasteaApplicationCurrentState = Adrastea_Application_SM_KaaIOT_Subscribe;
            }
            break;
        case AZURE:
            if (!ATMQTT_ParseConnectionConfirmationEvent(eventText,
                                                         &connResult))
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Azure_Connect;
            }
            else if (connResult.resultCode == ATMQTT_Event_Result_Code_Success)
            {
                printf("INFO : Azure Connection successfull !  \r\n");
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Azure_Subscribe;
            }
            break;
        }

        break;
    }

    case ATEvent_PacketDomain_Network_Registration_Status:
    {
        ATPacketDomain_ParseNetworkRegistrationStatusEvent(
            eventText,
            (ATPacketDomain_Network_Registration_Status_t *)&status);

        if (status.state != ATPacketDomain_Network_Registration_State_Registered_Roaming)
        {
            printf("ERROR : !!! Cellular network not available ! \r\n");
            adrasteaApplicationCurrentState = Adrastea_Application_SM_Network_Dropped;
        }
        if (status.state == ATPacketDomain_Network_Registration_State_Registered_Roaming)
        {
            if (!isNetworkInitialized){
                printf("INFO : !!! Cellular network available. It is initializing. ! \r\n");
                isNetworkInitialized = true;
                adrasteaApplicationCurrentState = Adrastea_Application_SM_CheckPingStatus;
            }
        }

        if (status.state == ATPacketDomain_Network_Registration_State_Unknown)
        {
            adrasteaApplicationCurrentState = Adrastea_Application_SM_Network_Dropped;
        }

        break;
    }

    case Adrastea_Application_SM_Network_Dropped:
    {
        printf("ERROR : R E S E T T I N G ....... ! \r\n");
        ATDevice_Reset();
        break;
    }

    case ATEvent_MQTT_Subscription_Confirmation:
    {
        ATMQTT_Subscription_Result_t subResult;

        switch (cloud_type)
        {
        case MOSQUITTO:
            if (!ATMQTT_ParseSubscriptionConfirmationEvent(eventText, &subResult))
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_Subscribe;
            }
            else
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Ready_Mosquitto;
            }
            break;
        case MOSQUITTO_TLS:
            if (!ATMQTT_ParseSubscriptionConfirmationEvent(eventText, &subResult))
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_TLS_Subscribe;
            }
            else
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Ready_Mosquitto_TLS;
            }
            break;
        case KAAIOT:
            if (!ATMQTT_ParseSubscriptionConfirmationEvent(eventText, &subResult))
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_KaaIOT_Subscribe;
            }
            else
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Ready_KaaIoT;
            }
            break;
        case AZURE:
            if (!ATMQTT_ParseSubscriptionConfirmationEvent(eventText, &subResult))
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Azure_Subscribe;
            }
            else
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Ready_Azure;
            }
            break;

        default:
            break;
        }
        break;
    }

    default:
        break;
    }
}

void Init__Cloud__Task()
{

    Adrastea_pins.Adrastea_Pin_WakeUp.pin = 6;

    if (!Adrastea_Init(&Adrastea_pins, 115200, WE_FlowControl_NoFlowControl,
                       WE_Parity_None, &Adrastea_EventCallback))
    {
        WE_DEBUG_PRINT("Adrastea was failed to initialized.... \r\n");
        adrasteaApplicationCurrentState = Adrastea_Application_SM_Idle;
        isNetworkInitialized =
         false;
    }

    printf(" --------->  APPLICATION_VERSION -------> : %s \r\n", APPLICATION_VERSION);

    while (true)
    {
        switch (adrasteaApplicationCurrentState)
        {

#pragma region Network_Connectivity_Setup
        case Adrastea_Application_SM_Idle:

            ATSIM_ReadPinStatus(&pinStatus);

            if (pinStatus == ATSIM_PIN_Status_Ready)
            {
                ATDevice_RequestIMEI(&imei_p);
                adrasteaApplicationCurrentState = Adrastea_Application_SM_SetNetworkState;
            }
            break;

        case Adrastea_Application_SM_SetNetworkState:
            if (ATProprietary_SetNetworkAttachmentState(ATProprietary_Network_State_Attach))
            {
                ATProprietary_SetNetworkAttachmentState(ATProprietary_Network_State_Attach);
                ATPacketDomain_SetNetworkRegistrationResultCode(ATPacketDomain_Network_Registration_Result_Code_Enable_with_Location_Info);
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Wait4NetworkRegistered;
            }

            break;

        case Adrastea_Application_SM_Wait4NetworkRegistered:

            ATPacketDomain_ReadNetworkRegistrationStatus(&networkRegistrationStatus);

            if (networkRegistrationStatus.state == ATPacketDomain_Network_Registration_State_Registered_Roaming)
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_CheckPingStatus;
            }
            break;

        case Adrastea_Application_SM_CheckPingStatus:
            pingOk = ATProprietary_Ping(ATProprietary_IP_Addr_Format_IPv4, "8.8.8.8",
                                        ATProprietary_Ping_Packet_Count_Invalid,
                                        ATProprietary_Ping_Packet_Size_Invalid,
                                        ATProprietary_Ping_Timeout_Invalid);
            if (pingOk)
            {
                adrasteaApplicationCurrentState = Adrastea_Application_SM_ReadCloudConfiguration;
            }
            break;

#pragma endregion Network_Connectivity_Setup
#pragma region Check_Cloud_Type

        case Adrastea_Application_SM_ReadCloudConfiguration:

            Read_Cloud_Settings_From_Flash(&p_cloud_settings);

            cloud_type = Get_Cloud_Type_From_Version(p_cloud_settings.cloud_version);

            switch (cloud_type)
            {
            case AWS:
                Read_AWS_Cloud_Settings_From_Flash(&p_cloud_aws, &p_cloud_settings);
                Read_AWS_Device_Certificate_From_Flash(&p_cloud_aws);
                Read_AWS_Private_Key_From_Flash(&p_cloud_aws);
                adrasteaApplicationCurrentState = Adrastea_Application_SM_AWSMQTT_Connect;
                break;
            case AZURE:
                Read_Azure_Cloud_Settings_From_Flash(&p_cloud_azure, &p_cloud_settings);
                Read_Azure_Device_Certificate_From_Flash(&p_cloud_azure);
                Read_Azure_Private_Key_From_Flash(&p_cloud_azure);
                Read_Azure_Root_Cert_From_Flash(&p_cloud_azure);
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Azure_Connect;
                break;
            case KAAIOT:
                Read_KaaIoT_Cloud_Settings(&p_cloud_kaaiot, &p_cloud_settings);
                adrasteaApplicationCurrentState = Adrastea_Application_SM_KaaIOT_Connect;
                break;
            case MOSQUITTO:
                Read_Mosquitto_Cloud_Settings(&p_cloud_mosquitto, &p_cloud_settings);
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_Connect;
                break;
            case MOSQUITTO_TLS:
                Read_Mosquitto_Cloud_Settings(&p_cloud_mosquitto, &p_cloud_settings);
                Read_Mosquitto_Client_Certificate_From_Flash(&p_cloud_mosquitto_cert);
                Read_Mosquitto_Client_Key_From_Flash(&p_cloud_mosquitto_cert);
                Read_Mosquitto_Root_Cert_From_Flash(&p_cloud_mosquitto_cert);
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_Connect_TLS;
                break;
            case UNKNOWN_CLOUD_TYPE:
                adrasteaApplicationCurrentState = Adrastea_Application_SM_Error;
                break;
            default:
                break;
            }
            WE_Delay(100);

            break;
#pragma endregion Check_Cloud_Type
#pragma region Mosquitto_Without_TLS
        case Adrastea_Application_SM_Mosquitto_Connect:

            ATMQTT_SetMQTTUnsolicitedNotificationEvents(ATMQTT_Event_All, ATCommon_Event_State_Enable);
            WE_Delay(10);
            ATMQTT_ConfigureNodes(ATMQTT_Conn_ID_Single_Connectivity_Mode,
                                  p_cloud_mosquitto.client_id,
                                  p_cloud_mosquitto.endpoint_url,
                                  NULL, NULL);
            WE_Delay(10);
            ATMQTT_Connect(ATMQTT_Conn_ID_Single_Connectivity_Mode);
            WE_Delay(100);
            break;

        case Adrastea_Application_SM_Mosquitto_Subscribe:

            if (p_cloud_mosquitto.subscribe_topics != NULL)
            {
                int size = sizeof(p_cloud_mosquitto.subscribe_topics) / sizeof(p_cloud_mosquitto.subscribe_topics[0]);

                for (int i = 0; i < size; i++)
                {
                    if (p_cloud_mosquitto.subscribe_topics[i] != NULL)
                    {
                        ATMQTT_Subscribe(ATMQTT_Conn_ID_Single_Connectivity_Mode,
                                         atoi(p_cloud_mosquitto.qos),
                                         p_cloud_mosquitto.subscribe_topics[i]);

                        WE_Delay(1000);
                    }
                }
            }

            break;

        case Adrastea_Application_SM_Mosquitto_PublishData:

            data = Get_Sensor_Data(imei_p);

            payload = Convert_Sensor_Data_to_JSON(data);

            ATMQTT_Publish(ATMQTT_Conn_ID_Single_Connectivity_Mode, ATMQTT_QoS_At_Least_Once, ATMQTT_Retain_Retained,
                           p_cloud_mosquitto.publish_topic, payload, strlen(payload));

            free(payload);

            adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_PublishData;
            WE_Delay(PUBLISH_FREQ);

            break;
#pragma endregion Mosquitto_Without_TLS
#pragma region AWS_IoT_Core_Connectivity

        case Adrastea_Application_SM_AWSMQTT_Connect:

            ATProprietary_WriteCredential(p_cloud_aws.aws_device_cert_file_name,
                                          ATProprietary_Credential_Format_Certificate,
                                          p_cloud_aws.aws_device_cert_content);

            WE_Delay(10);

            ATProprietary_WriteCredential(p_cloud_aws.aws_private_key_file_name,
                                          ATProprietary_Credential_Format_Private_Key,
                                          p_cloud_aws.aws_private_key_content);
            WE_Delay(10);

            /*Set TLS Profile */
            ATProprietary_AddTLSProfile(1, NULL, NULL,
                                        p_cloud_aws.aws_device_cert_file_name,
                                        p_cloud_aws.aws_private_key_file_name,
                                        NULL,
                                        NULL);
            WE_Delay(10);
            /*  Allow AWS events*/
            ATMQTT_SetAWSIOTUnsolicitedNotificationEvents(ATMQTT_Event_All, ATCommon_Event_State_Enable);
            WE_Delay(10);

            /* Connect an AWS session*/
            ATMQTT_AWSIOTConfigureConnection(p_cloud_aws.endpoint_url, 1, p_cloud_aws.client_id);
            WE_Delay(10);

            ATMQTT_AWSIOTConfigureProtocol(atoi(p_cloud_aws.keep_alive_time), ATMQTT_AWSIOT_QoS_No_Confirmation);
            WE_Delay(10);
            ATMQTT_AWSIOTConnect();
            WE_Delay(5000);
            break;

        case Adrastea_Application_SM_AWSMQTT_Subscribe:

            if (p_cloud_aws.subscribe_topics != NULL)
            {
                int size = sizeof(p_cloud_aws.subscribe_topics) / sizeof(p_cloud_aws.subscribe_topics[0]);

                for (int i = 0; i < size; i++)
                {
                    if (p_cloud_aws.subscribe_topics[i] != NULL)
                    {
                        ATMQTT_AWSIOTSubscribe(p_cloud_aws.subscribe_topics[i]);
                        WE_Delay(1000);
                    }
                }
            }

            break;

        case Adrastea_Application_SM_AWSMQTT_PublishData:

            data = Get_Sensor_Data(imei_p);

            payload = Convert_Sensor_Data_to_JSON(data);

            size_of_payload = strlen(payload);
            size_of_payload = size_of_payload * 2;

            char *payload_formatted = malloc(size_of_payload);

            Replace_DoubleQuotes_With_Escape(payload, payload_formatted);

            ATMQTT_AWSIOTPublish(p_cloud_aws.publish_topic, payload_formatted);

            free(payload);
            free(payload_formatted);

            WE_Delay(PUBLISH_FREQ);
            adrasteaApplicationCurrentState = Adrastea_Application_SM_AWSMQTT_PublishData;
            break;

#pragma endregion AWS_IoT_Core_Connectivity
#pragma region Azure_IoT_Core_Connectivity
        case Adrastea_Application_SM_Azure_Connect:

            ATProprietary_WriteCredential(p_cloud_azure.azure_root_cert_file_name,
                                          ATProprietary_Credential_Format_Certificate,
                                          p_cloud_azure.azure_root_cert_content);
            WE_Delay(1000);

            ATProprietary_WriteCredential(p_cloud_azure.azure_device_cert_file_name,
                                          ATProprietary_Credential_Format_Certificate,
                                          p_cloud_azure.azure_device_cert_content);

            WE_Delay(1000);

            ATProprietary_WriteCredential(p_cloud_azure.azure_private_key_file_name,
                                          ATProprietary_Credential_Format_Private_Key,
                                          p_cloud_azure.azure_private_key_content);
            WE_Delay(1000);

            /*Set TLS Profile */
            ATProprietary_AddTLSProfile(1,
                                        p_cloud_azure.azure_root_cert_file_name,
                                        NULL,
                                        p_cloud_azure.azure_device_cert_file_name,
                                        p_cloud_azure.azure_private_key_file_name,
                                        NULL,
                                        NULL);

            WE_Delay(2000);

            ATMQTT_SetMQTTUnsolicitedNotificationEvents(ATMQTT_Event_All, ATCommon_Event_State_Enable);
            WE_Delay(100);

            ATMQTT_ConfigureNodes(ATMQTT_Conn_ID_1,
                                  p_cloud_azure.client_id,
                                  p_cloud_azure.endpoint_url,
                                  p_cloud_azure.user_name, NULL);
            WE_Delay(3000);

            ATMQTT_ConfigureProtocol(ATMQTT_Conn_ID_1, atoi(p_cloud_azure.keep_alive_time), ATMQTT_Clean_Session_Discard_After_Disconnect);
            WE_Delay(1000);
            ATMQTT_ConfigureIP(ATMQTT_Conn_ID_1, ATMQTT_IP_Session_ID_Invalid, ATMQTT_IP_Addr_Format_IPv4v6, atoi(p_cloud_azure.port_number));
            WE_Delay(100);
            ATMQTT_ConfigureTLS(ATMQTT_Conn_ID_1, ATCommon_Auth_Mode_Mutual, 1);
            WE_Delay(100);

            ATMQTT_Connect(ATMQTT_Conn_ID_1);
            WE_Delay(2000);

            break;
        case Adrastea_Application_SM_Azure_Subscribe:

            ATMQTT_Subscribe(ATMQTT_Conn_ID_1, ATMQTT_QoS_At_Most_Once, p_cloud_azure.subscribe_topic);
            WE_Delay(2000);
            break;

        case Adrastea_Application_SM_Azure_PublishData:

            data = Get_Sensor_Data(imei_p);

            payload = Convert_Sensor_Data_to_JSON(data);

            size_of_payload = strlen(payload);
            size_of_payload = size_of_payload * 2;

            payload_formatted = malloc(size_of_payload);

            Replace_DoubleQuotes_With_Escape(payload, payload_formatted);

            ATMQTT_Publish(ATMQTT_Conn_ID_1,
                           ATMQTT_QoS_At_Most_Once,
                           ATMQTT_Retain_Retained,
                           p_cloud_azure.publish_topic,
                           payload, strlen(payload));

            free(payload);
            free(payload_formatted);

            adrasteaApplicationCurrentState = Adrastea_Application_SM_Azure_PublishData;
            WE_Delay(PUBLISH_FREQ);
            break;

#pragma endregion Azure_IoT_Core_Connectivity
#pragma region Mosquitto_TLS_Connectivity
        case Adrastea_Application_SM_Mosquitto_Connect_TLS:

            ATProprietary_WriteCredential(p_cloud_mosquitto_cert.mosquitto_root_cert_file_name,
                                          ATProprietary_Credential_Format_Certificate,
                                          p_cloud_mosquitto_cert.mosquitto_root_cert_content);
            WE_Delay(3000);

            ATProprietary_WriteCredential(p_cloud_mosquitto_cert.client_cert_file_name,
                                          ATProprietary_Credential_Format_Certificate,
                                          p_cloud_mosquitto_cert.client_cert_content);

            WE_Delay(3000);

            ATProprietary_WriteCredential(p_cloud_mosquitto_cert.client_key_file_name,
                                          ATProprietary_Credential_Format_Private_Key,
                                          p_cloud_mosquitto_cert.client_key_content);
            WE_Delay(3000);

            /*Set TLS Profile */
            ATProprietary_AddTLSProfile(1,
                                        p_cloud_mosquitto_cert.mosquitto_root_cert_file_name,
                                        NULL,
                                        p_cloud_mosquitto_cert.client_cert_file_name,
                                        p_cloud_mosquitto_cert.client_key_file_name,
                                        NULL,
                                        NULL);

            WE_Delay(2000);

            ATMQTT_SetMQTTUnsolicitedNotificationEvents(ATMQTT_Event_All, ATCommon_Event_State_Enable);
            WE_Delay(2000);

            ATMQTT_ConfigureNodes(ATMQTT_Conn_ID_1,
                                  p_cloud_mosquitto.client_id,
                                  p_cloud_mosquitto.endpoint_url,
                                  NULL,
                                  NULL);
            WE_Delay(2000);

            ATMQTT_ConfigureProtocol(ATMQTT_Conn_ID_1, atoi(p_cloud_mosquitto.keep_alive_time), ATMQTT_Clean_Session_Discard_After_Disconnect);

            ATMQTT_ConfigureIP(ATMQTT_Conn_ID_1,
                               ATMQTT_IP_Session_ID_Invalid,
                               ATMQTT_IP_Addr_Format_IPv4v6,
                               atoi(p_cloud_mosquitto.port_number));

            ATMQTT_ConfigureTLS(ATMQTT_Conn_ID_1, ATCommon_Auth_Mode_Mutual, 1);
            WE_Delay(2000);

            ATMQTT_Connect(ATMQTT_Conn_ID_1);
            WE_Delay(2000);

            break;
        case Adrastea_Application_SM_Mosquitto_TLS_Subscribe:

            if (p_cloud_mosquitto.subscribe_topics != NULL)
            {
                int size = sizeof(p_cloud_mosquitto.subscribe_topics) / sizeof(p_cloud_mosquitto.subscribe_topics[0]);

                for (int i = 0; i < size; i++)
                {
                    if (p_cloud_mosquitto.subscribe_topics[i] != NULL)
                    {
                        ATMQTT_Subscribe(ATMQTT_Conn_ID_1, atoi(p_cloud_mosquitto.qos),
                                         p_cloud_mosquitto.subscribe_topics[i]);

                        WE_Delay(1000);
                    }
                }
            }

            adrasteaApplicationCurrentState = Adrastea_Application_SM_Ready_Mosquitto_TLS;

            break;
        case Adrastea_Application_SM_Mosquitto_TLS_PublishData:
            data = Get_Sensor_Data(imei_p);

            payload = Convert_Sensor_Data_to_JSON(data);

            ATMQTT_Publish(ATMQTT_Conn_ID_1,
                           atoi(p_cloud_mosquitto.qos),
                           ATMQTT_Retain_Retained,
                           p_cloud_mosquitto.publish_topic,
                           payload, strlen(payload));
            free(payload);

            adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_TLS_PublishData;

            WE_Delay(PUBLISH_FREQ);

            break;
#pragma endregion Mosquitto_TLS_Connectivity
#pragma region KaaIoT_Connectivity
        case Adrastea_Application_SM_KaaIOT_Connect:

            ATMQTT_SetMQTTUnsolicitedNotificationEvents(ATMQTT_Event_All, ATCommon_Event_State_Enable);
            WE_Delay(100);
            ATMQTT_ConfigureNodes(ATMQTT_Conn_ID_Single_Connectivity_Mode,
                                  p_cloud_kaaiot.client_id,
                                  p_cloud_kaaiot.endpoint_url,
                                  NULL,
                                  NULL);
            WE_Delay(10);
            ATMQTT_Connect(ATMQTT_Conn_ID_Single_Connectivity_Mode);

            WE_Delay(2000);
            break;

            break;
        case Adrastea_Application_SM_KaaIOT_Subscribe:

            ATMQTT_Subscribe(ATMQTT_Conn_ID_Single_Connectivity_Mode,
                             atoi(p_cloud_kaaiot.qos),
                             p_cloud_kaaiot.subscribe_topic);

            WE_Delay(1000);

            break;
        case Adrastea_Application_SM_KaaIOT_PublishData:

            data = Get_Sensor_Data(imei_p);

            payload = Convert_Sensor_Data_to_JSON(data);

            ATMQTT_Publish(ATMQTT_Conn_ID_Single_Connectivity_Mode, ATMQTT_QoS_At_Least_Once,
                           ATMQTT_Retain_Retained,
                           p_cloud_kaaiot.publish_topic,
                           payload,
                           strlen(payload));

            free(payload);

            adrasteaApplicationCurrentState = Adrastea_Application_SM_KaaIOT_PublishData;
            WE_Delay(PUBLISH_FREQ);

            break;
#pragma endregion KaaIoT_Connectivity

        case Adrastea_Application_SM_Ready_Mosquitto_TLS:
            adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_TLS_PublishData;
            break;
        case Adrastea_Application_SM_Ready_AWS:
            adrasteaApplicationCurrentState = Adrastea_Application_SM_AWSMQTT_PublishData;
            break;
        case Adrastea_Application_SM_Ready_Azure:
            adrasteaApplicationCurrentState = Adrastea_Application_SM_Azure_PublishData;
            break;
        case Adrastea_Application_SM_Ready_Mosquitto:
            adrasteaApplicationCurrentState = Adrastea_Application_SM_Mosquitto_PublishData;
            break;
        case Adrastea_Application_SM_Ready_KaaIoT:
            adrasteaApplicationCurrentState = Adrastea_Application_SM_KaaIOT_PublishData;
            break;
        case Adrastea_Application_SM_Error:
            WE_DEBUG_PRINT("Unknown Cloud Type");
            break;
        default:
            break;
        }

        WE_Delay(1000);
    }
}
