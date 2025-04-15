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

TaskHandle_t Task_Handler = NULL;

/* Comment/uncomment the following lines to disable/enable the examples for
 * each data type (see main function). */
/* Note: The float example won't compile unless WE_USE_FLOAT is defined. */
#define TIDS_EXAMPLE_ENABLE_FLOAT
#define TIDS_EXAMPLE_ENABLE_INT


/* Sensor interface configuration */
static WE_sensorInterface_t tids, hids, itds, pads;
static Sensor_Data_t sensor_data;

void Init__Sensor_Task(void);

void HAL_Init(void);

void Sensors_Init();

static bool Initialize_TIDS();
static bool Initialize_HIDS();
static bool Initialize_PADS();
static bool Initialize_ITDS();

static bool read_Hids(float *humidity, float *temp);
static bool read_Tids(float *temp);
static bool read_Itds(float *accelX, float *accelY, float *accelZ, float *temp);
static bool read_Pads(float *pressure, float *temp_float, int16_t *temp_int);

static void Sensor_Monitor();


float round(float num)
{
    // Add 0.5 to the number and truncate the result
    int rounded = (int)(num + 0.5);
    // Return the rounded integer value
    return (float)rounded;
}


void Init__Sensor()
{

    xTaskCreate(Init__Sensor_Task,      /* The function that implements the task. */
                "Init__Sensor_Task",    /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                configMINIMAL_STACK_SIZE * 2, /* The size of the stack to allocate to the task. */
                (void *)NULL,                 /* The parameter passed to the task */
                configMAX_PRIORITIES - 2,     /* The priority assigned to the task - minimal priority. */
                &Task_Handler);

    return WE_SUCCESS;
}

void Init__Sensor_Task()
{
    //sensor_data = NULL ;
    HAL_Init(); /* Initialize the related HAL Interface. e.g I2C */

    Sensors_Init(); /* Initialize the Sensor interfaces */
    
    Sensor_Monitor();
}

void HAL_Init(void)
{
    uint8_t ret = 0;

    /*Set Bus Id*/
    HAL_I2C__Set_I2C_Bus_Id(HAL_I2C_BusId_0);

    /*Initiliaze the I2C*/
    HAL_I2C__Initialize();

    /*Set Power Control*/
    HAL_I2C__SetPowerMode(HAL_I2C_POWER_FULL);

    /*Sets the speed */
    HAL__I2C_SetSpeed(100);

    HAL__I2C_SetOpMode(0);

    WE_Delay(5);
}

void Sensors_Init()
{
    Initialize_TIDS();
    Initialize_HIDS();
    Initialize_PADS();
    Initialize_ITDS();
}


Sensor_Data_t Get_Sensor_Data(char* device_id)
{
    //Set the device id
    sensor_data._deviceId = malloc( strlen(device_id) + 1 );
 
    strcpy(sensor_data._deviceId , device_id);

    return sensor_data;
}

static void Sensor_Monitor()
{
    float temp_tids = 0;
    float temp_pad_float = 0;
    int16_t temp_pad_int = 0;
    float pressure_pad = 0;
    float temp_itds = 0;
    float itds_x = 0;
    float itds_y = 0;
    float itds_z = 0;
    float temp_hids = 0;
    float humid_hids = 0;

    while (true)
    {

        read_Pads(&pressure_pad, &temp_pad_float, &temp_pad_int);
        read_Tids(&temp_tids);
        read_Itds(&itds_x, &itds_y, &itds_z, &temp_itds);
        read_Hids(&humid_hids, &temp_hids);

        sensor_data._Pads.pressure = pressure_pad;
        sensor_data._Pads.temperature_float = temp_pad_float;
        sensor_data._Pads.temperature_int = temp_pad_int;

        sensor_data._Tids.temperature = temp_tids;

        sensor_data._Itds.temperature = temp_itds;

        sensor_data._Itds.accelX = itds_x;
        sensor_data._Itds.accelY = itds_y;
        sensor_data._Itds.accelZ = itds_z;

        sensor_data._Hids.temperature = temp_hids;
        sensor_data._Hids.humidity = humid_hids;
    }
}

static bool Initialize_TIDS()
{

    /* Initialize sensor interface (i2c with TIDS address, burst mode deactivated) */
    TIDS_getDefaultInterface(&tids);

    while (WE_SUCCESS != WE_isSensorInterfaceReady(&tids))
    {
    }

    const uint8_t deviceIdValue = 0;

    if (WE_SUCCESS == TIDS_getDeviceID(&tids, &deviceIdValue))
    {

        char ReturnValue_Str[3];
        char DeviceIdValue_Str[3];

        sprintf(ReturnValue_Str, "%d", deviceIdValue);
        sprintf(DeviceIdValue_Str, "%d", TIDS_DEVICE_ID_VALUE);

        int ReturnValue_Converted = atoi(ReturnValue_Str);
        int deviceIdValue_Converted = atoi(DeviceIdValue_Str);

        if (ReturnValue_Converted == deviceIdValue_Converted) /* who am i ? - i am WSEN-TIDS! */
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

static bool Initialize_HIDS()
{
    int8_t status = WE_FAIL;
    uint8_t deviceIdValue = 0;
    HIDS_getDefaultInterface(&hids);

    if (WE_SUCCESS == HIDS_getDeviceID(&hids, &deviceIdValue))
    {

        char ReturnValue_Str[3];
        char DeviceIdValue_Str[3];

        sprintf(ReturnValue_Str, "%d", deviceIdValue);
        sprintf(DeviceIdValue_Str, "%d", HIDS_DEVICE_ID_VALUE);

        int ReturnValue_Converted = atoi(ReturnValue_Str);
        int deviceIdValue_Converted = atoi(DeviceIdValue_Str);

        if (ReturnValue_Converted == deviceIdValue_Converted) /* who am i ? - i am WSEN-HIDS! */
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    /*enable Block Data Update*/
    status = HIDS_enableBlockDataUpdate(&hids, HIDS_enable);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    /*Set ODR to one shot mode*/
    status = HIDS_setOutputDataRate(&hids, HIDS_oneShot);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    /*Power mode to active*/
    status = HIDS_setPowerMode(&hids, HIDS_activeMode);
    if (status != WE_SUCCESS)
    {
        return false;
    }
    return true;
}

static bool Initialize_PADS()
{
    int8_t status = WE_FAIL;
    uint8_t deviceIdValue = 0;

    PADS_getDefaultInterface(&pads);

    /* first communication test - WSEN_PADS*/
    if (PADS_getDeviceID(&pads, &deviceIdValue) == WE_SUCCESS)
    {
        char ReturnValue_Str[3];
        char DeviceIdValue_Str[3];

        sprintf(ReturnValue_Str, "%d", deviceIdValue);
        sprintf(DeviceIdValue_Str, "%d", PADS_DEVICE_ID_VALUE);

        int ReturnValue_Converted = atoi(ReturnValue_Str);
        int deviceIdValue_Converted = atoi(DeviceIdValue_Str);

        if (ReturnValue_Converted == deviceIdValue_Converted) /* who am i ? - i am WSEN-TIDS! */
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    /*set ODR to Power down*/
    status = PADS_setOutputDataRate(&pads, PADS_outputDataRatePowerDown);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    /*set low pass filter to BW=ODR/20*/

    status = PADS_setLowPassFilterConfig(&pads, PADS_lpFilterBW2);
    if (status != WE_SUCCESS)
    {
        return false;
    }
    /*enable low pass filter */
    status = PADS_enableLowPassFilter(&pads, PADS_enable);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    /*enable Block Data Update*/
    status = PADS_enableBlockDataUpdate(&pads, PADS_enable);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    /*select Power Mode [0:low Current Mode; 1:low noise Mode]*/
    status = PADS_setPowerMode(&pads, PADS_lowNoise);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    /*enable the Auto Increment */
    status = PADS_enableAutoIncrement(&pads, PADS_enable);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    return true;
}

static bool Initialize_ITDS()
{

    int8_t status = WE_FAIL;
    uint8_t deviceIdValue = 0;

    ITDS_getDefaultInterface(&itds);

    /* first communication test - WSEN_ITDS*/
    if (ITDS_getDeviceID(&itds, &deviceIdValue) == WE_SUCCESS)
    {
        char ReturnValue_Str[3];
        char DeviceIdValue_Str[3];

        sprintf(ReturnValue_Str, "%d", deviceIdValue);
        sprintf(DeviceIdValue_Str, "%d", ITDS_DEVICE_ID_VALUE);

        int ReturnValue_Converted = atoi(ReturnValue_Str);
        int deviceIdValue_Converted = atoi(DeviceIdValue_Str);

        if (ReturnValue_Converted == deviceIdValue_Converted) /* who am i ? - i am WSEN-TIDS! */
        {
            //printf("WSEN_ITDS Communication success\r\n \r\n");
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    // /*Enable high performance mode*/
    status = ITDS_setOperatingMode(&itds, ITDS_highPerformance);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    // /*Sampling rate of 400 Hz*/
    status = ITDS_setOutputDataRate(&itds, ITDS_odr7);
    if (status != WE_SUCCESS)
    {
        return false;
    }
    status = ITDS_setPowerMode(&itds, ITDS_normalMode);
    if (status != WE_SUCCESS)
    {
        return false;
    }
    /*Enable block data update*/
    status = ITDS_enableBlockDataUpdate(&itds, ITDS_enable);
    if (status != WE_SUCCESS)
    {
        return false;
    }
    /*Enable address auto increment*/
    status = ITDS_enableAutoIncrement(&itds, ITDS_enable);
    if (status != WE_SUCCESS)
    {
        return false;
    }
    // /*2g*/
    status = ITDS_setFullScale(&itds, ITDS_twoG);
    if (status != WE_SUCCESS)
    {
        return false;
    }
    /*Filter bandwidth = ODR/2*/
    status =
        ITDS_setFilteringCutoff(&itds, ITDS_outputDataRate_2);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    status = ITDS_enableLowNoise(&itds, ITDS_enable);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    ITDS_enableDoubleTapEvent(&itds, ITDS_enable);

    /* Corresponds to 4 * 2 / 32 = 0.25 g */
    ITDS_setTapThresholdX(&itds, 4);
    ITDS_setTapThresholdY(&itds, 4);
    ITDS_setTapThresholdZ(&itds, 4);

    /* Enable tap recognition for x, y and z */
    ITDS_enableTapX(&itds, ITDS_enable);
    ITDS_enableTapY(&itds, ITDS_enable);
    ITDS_enableTapZ(&itds, ITDS_enable);

    /* Set priority z-y-x */
    ITDS_setTapAxisPriority(&itds, ITDS_Z_Y_X);

    /* Set quiet time (1 bit = 1 * 4 / ODR) */
    /* Corresponds to 1 * 4 / 400 = 10 ms */
    ITDS_setTapQuietTime(&itds, 1);

    /* Set shock time (1 bit = 1 * 8 / ODR) */
    /* Corresponds to 2 * 8 / 400 = 40 ms */
    ITDS_setTapShockTime(&itds, 2);

    /* Set latency time (1 bit = 1 * 32 / ODR) */
    /* Corresponds to 5 * 32 / 400 = 400 ms */
    ITDS_setTapLatencyTime(&itds, 5);

    /* Set minimum fall duration (1 bit = 1 * 1 / ODR) */
    /* Corresponds to 6 / 200 = 30 ms */
    ITDS_setFreeFallDurationLSB(&itds, 6);

    /* Set free-fall threshold (value is encoded - see documentation of
     * FREE_FALL_REG for details) */
    /* Corresponds to 10 * 31.25mg = 312.5mg */
    ITDS_setFreeFallThreshold(&itds, ITDS_ten);

    /* Interrupts are active high */
    ITDS_setInterruptActiveLevel(&itds, ITDS_activeHigh);

    // /* Interrupts are push-pull */
    ITDS_setInterruptPinType(&itds, ITDS_pushPull);

    /* Latched mode */
    ITDS_enableLatchedInterrupt(&itds, ITDS_enable);

    /* Enable interrupts */
    ITDS_enableInterrupts(&itds, ITDS_enable);

    ITDS_enableDoubleTapINT0(&itds, ITDS_enable);

    ITDS_enableFreeFallINT0(&itds, ITDS_enable);

    return true;
}

static bool read_Tids(float *temp)
{
    // TIDS_init();
    WE_Delay(100);

    int8_t status = WE_FAIL;

    TIDS_state_t temperatureDataStatus = TIDS_enable;

    /* Perform software reset */
    status = TIDS_softReset(&tids, TIDS_enable);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    WE_Delay(10);

    status = TIDS_softReset(&tids, TIDS_disable);

    if (status != WE_SUCCESS)
    {
        return false;
    }

    /* Enable auto address increment */
    TIDS_enableAutoIncrement(&tids, TIDS_enable);

    TIDS_enableOneShot(&tids, TIDS_enable);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    /*check the temp Data status*/
    do
    {
        if (TIDS_isBusy(&tids, &temperatureDataStatus) !=
            WE_SUCCESS)
        {
            return false;
        }
        WE_Delay(5);
    } while (temperatureDataStatus == TIDS_enable);

    if (status != WE_SUCCESS)
    {
        return false;
    }

    if (temp)
    {
        status = TIDS_getTemperature(&tids, temp);
        if (status != WE_SUCCESS)
        {
            return false;
        }
        /*Round to 2 decimal places*/
    }

    return true;
}

#define WE_USE_FLOAT

static bool read_Pads(float *pressure, float *temp_float, int16_t *temp_int)
{
    int8_t status = WE_FAIL;

    WE_Delay(100);

    PADS_getDefaultInterface(&pads);

    status = PADS_enableOneShot(&pads, PADS_enable);

    if (status != WE_SUCCESS)
    {
        return false;
    }

    WE_Delay(15);

    if (pressure)
    {
        status = PADS_getPressure_float(&pads, pressure);
        if (status != WE_SUCCESS)
        {
            return false;
        }
        /*Round to 3 decimal places*/
    }

    PADS_state_t state_temp;
    PADS_state_t state_pressure;

    if (temp_float)
    {

        status = PADS_getTemperature_float(&pads, temp_float);
        if (status != WE_SUCCESS)
        {
            return false;
        }
    }

    if (temp_int)
    {
        status = PADS_getTemperature_int(&pads, temp_int);
        if (status != WE_SUCCESS)
        {
            return false;
        }
    }

    return true;
}

static bool read_Itds(float *accelX, float *accelY, float *accelZ, float *temp)
{

    int8_t status = WE_FAIL;
    ITDS_state_t DRDY = ITDS_disable;
    int16_t XRawAcc = 0, YRawAcc = 0, ZRawAcc = 0;

    status = ITDS_isAccelerationDataReady(&itds, &DRDY);
    if (status != WE_SUCCESS)
    {
        return false;
    }

    if (DRDY == ITDS_enable)
    {
        if (accelX)
        {
            status = ITDS_getRawAccelerationX(&itds, &XRawAcc);
            if (status != WE_SUCCESS)
            {
                return false;
            }
            XRawAcc = XRawAcc >> 2;
            *accelX = (float)(XRawAcc);
            *accelX = *accelX / 1000;
            *accelX = *accelX * 0.244;
            /*Round to 3 decimal places*/
            *accelX = round(*accelX * 1000) / (float)1000;
        }

        if (accelY)
        {
            status = ITDS_getRawAccelerationY(&itds, &YRawAcc);
            if (status != WE_SUCCESS)
            {
                return false;
            }
            YRawAcc = YRawAcc >> 2;
            *accelY = (float)(YRawAcc);
            *accelY = *accelY / 1000;
            *accelY = *accelY * 0.244;
            /*Round to 3 decimal places*/
            *accelY = round(*accelY * 1000) / (float)1000;
        }

        if (accelZ)
        {
            status = ITDS_getRawAccelerationZ(&itds, &ZRawAcc);
            if (status != WE_SUCCESS)
            {
                return false;
            }
            ZRawAcc = ZRawAcc >> 2;
            *accelZ = (float)(ZRawAcc);
            *accelZ = *accelZ / 1000;
            *accelZ = *accelZ * 0.244;
            /*Round to 3 decimal places*/
            *accelZ = round(*accelZ * 1000) / (float)1000;
        }

        if (temp)
        {
            status = ITDS_getTemperature12bit(&itds, temp);
            if (status != WE_SUCCESS)
            {
                return false;
            }
        }
    }
    else
    {
        //printf("ITDS data not ready\r\n");
        return false;
    }

    return true;
}

static bool read_Hids(float *humidity, float *temp)
{
    WE_Delay(100);

    int8_t status = WE_FAIL;
    HIDS_state_t humStatus = HIDS_disable, tempStatus = HIDS_disable;
    /*Start a conversion*/

    if (WE_FAIL == HIDS_enableOneShot(&hids, HIDS_enable))
    {
    }

    // Get status of data
    HIDS_isHumidityDataAvailable(&hids, &humStatus);
    HIDS_isTemperatureDataAvailable(&hids, &tempStatus);

    /*check the data status*/
    if (humStatus == HIDS_enable && tempStatus == HIDS_enable)
    {
        if (humidity)
        {
            status = HIDS_getHumidity_float(&hids, humidity);
            if (status != WE_SUCCESS)
            {
                return false;
            }
            /*Round to 2 decimal places*/
            *humidity = round(*humidity * 100) / (float)100;
        }

        if (temp)
        {
            status = HIDS_getTemperature_float(&hids, temp);
            if (status != WE_SUCCESS)
            {
                return false;
            }
            /*Round to 2 decimal places*/
            *temp = round(*temp * 100) / (float)100;
        }
    }
    else
    {
        return false;
    }

    return true;
}
