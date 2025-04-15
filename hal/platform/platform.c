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

#include "hal_helper.h"
#include "hal_common.h"
#include "platform.h"

#ifdef HAL_I2C_MODULE_ENABLED_ALT1250

static HAL_StatusTypeDef I2Cx_ReadBytes(uint8_t addr,
                                        uint16_t reg,
                                        uint16_t numBytesToRead,
                                        uint8_t slaveTransmitterMode,
                                        uint16_t timeout,
                                        uint8_t *value);

static HAL_StatusTypeDef I2Cx_WriteBytes(uint8_t addr,
                                         uint16_t reg,
                                         uint16_t numBytesToWrite,
                                         uint16_t timeout,
                                         uint8_t *value);

#endif /*#ifdef HAL_I2C_MODULE_ENABLED_ALT1250*/

#ifdef HAL_SPI_MODULE_ENABLED_ALT1250

static HAL_StatusTypeDef SPIx_ReadBytes(uint16_t chipSelectPin,
                                        uint8_t reg,
                                        uint16_t numBytesToRead,
                                        uint16_t timeout,
                                        uint8_t *value);
static HAL_StatusTypeDef SPIx_WriteBytes(uint16_t chipSelectPin,
                                         uint8_t reg,
                                         uint16_t numBytesToWrite,
                                         uint16_t timeout,
                                         uint8_t *value);

#endif /* HAL_SPI_MODULE_ENABLED_ALT1250 */

inline int8_t WE_ReadReg(WE_sensorInterface_t *interface,
                         uint8_t regAdr,
                         uint16_t numBytesToRead,
                         uint8_t *data)
{
    HAL_StatusTypeDef status = HAL_OK;

    switch (interface->interfaceType)
    {
    case WE_i2c_fifo:

#ifdef HAL_I2C_MODULE_ENABLED_ALT1250
        if (numBytesToRead > 1 && interface->options.i2c.useRegAddrMsbForMultiBytesRead)
        {
            /* Register address most significant bit is used to enable multi bytes read */
            regAdr |= 1 << 7;
        }

        status = I2Cx_ReadBytes(interface->options.i2c.address,
                                (uint16_t)regAdr,
                                numBytesToRead,
                                interface->options.i2c.slaveTransmitterMode,
                                interface->options.readTimeout,
                                data);
#else
        status = HAL_ERROR;
#endif /* HAL_I2C_MODULE_ENABLED_ALT1250 */
        break;

    case WE_i2c:
#ifdef HAL_I2C_MODULE_ENABLED_ALT1250

        if (numBytesToRead > 1 && interface->options.i2c.useRegAddrMsbForMultiBytesRead)
        {
            /* Register address most significant bit is used to enable multi bytes read */
            regAdr |= 1 << 7;
        }
        status = I2Cx_ReadBytes(interface->options.i2c.address,
                                (uint16_t)regAdr,
                                numBytesToRead,
                                interface->options.i2c.slaveTransmitterMode,
                                interface->options.readTimeout,
                                data);

#else
        status = HAL_ERROR;
#endif /* HAL_I2C_MODULE_ENABLED_ALT1250 */
        break;

    case WE_spi:
#ifdef HAL_SPI_MODULE_ENABLED_ALT1250
        if (interface->options.spi.burstMode != 0 || numBytesToRead == 1)
        {
            status = SPIx_ReadBytes((uint16_t)regAdr,
                                    numBytesToRead,
                                    interface->options.i2c.slaveTransmitterMode,
                                    interface->options.readTimeout,
                                    data);
        }

#else
        status = HAL_ERROR;
#endif /* HAL_SPI_MODULE_ENABLED */
        break;

    default:
        status = HAL_ERROR;
        break;
    }

    return status == HAL_OK ? WE_SUCCESS : WE_FAIL;
}

inline int8_t WE_WriteReg(WE_sensorInterface_t *interface,
                          uint8_t regAdr,
                          uint16_t numBytesToWrite,
                          uint8_t *data)
{
    HAL_StatusTypeDef status = HAL_OK;

    switch (interface->interfaceType)
    {

    case WE_i2c_fifo:
#ifdef HAL_I2C_MODULE_ENABLED_ALT1250
        if (interface->options.i2c.burstMode != 0 || numBytesToWrite == 1)
        {
            status = I2Cx_WriteBytes(interface->options.i2c.address,
                                     regAdr,
                                     numBytesToWrite,
                                     interface->options.writeTimeout,
                                     data);
        }
#else
        status = HAL_ERROR;
#endif /* HAL_I2C_MODULE_ENABLED_ALT1250 */
        break;

    case WE_i2c:
#ifdef HAL_I2C_MODULE_ENABLED_ALT1250
        if (interface->options.i2c.burstMode != 0 || numBytesToWrite == 1)
        {
            status = I2Cx_WriteBytes(interface->options.i2c.address,
                                     regAdr,
                                     numBytesToWrite,
                                     interface->options.writeTimeout,
                                     data);
        }

#else
        status = HAL_ERROR;
#endif /* HAL_I2C_MODULE_ENABLED_ALT1250 */
        break;

    case WE_spi:
#ifdef HAL_SPI_MODULE_ENABLED_ALT1250
        if (interface->options.spi.burstMode != 0 || numBytesToWrite == 1)
        {
            status = SPIx_WriteBytes(interface->options.spi.chipSelectPin,
                                     regAdr,
                                     numBytesToWrite,
                                     interface->options.writeTimeout,
                                     data);
        }

#else
        status = HAL_ERROR;
#endif /* HAL_SPI_MODULE_ENABLED_ALT1250 */
        break;

    default:
        status = HAL_ERROR;
        break;
    }

    return status == HAL_OK ? WE_SUCCESS : WE_FAIL;
}

int8_t WE_isSensorInterfaceReady(WE_sensorInterface_t *interface)
{
    switch (interface->interfaceType)
    {
    case WE_i2c:
#ifdef HAL_I2C_MODULE_ENABLED_ALT1250
        return (HAL_OK == HAL_I2C_IsDeviceReady(interface->options.i2c.address << 1,
                                                64,
                                                5000))
                   ? WE_SUCCESS
                   : WE_FAIL;
        return WE_SUCCESS;
#else
        return WE_FAIL;
#endif

    case WE_spi:
#ifdef HAL_SPI_MODULE_ENABLED_ALT1250
        return WE_SUCCESS;
#else
        return WE_FAIL;
#endif
    default:
        return WE_FAIL;
    }
}

#ifdef HAL_I2C_MODULE_ENABLED_ALT1250

static HAL_StatusTypeDef I2Cx_ReadBytes(uint8_t addr,
                                        uint16_t reg,
                                        uint16_t numBytesToRead,
                                        uint8_t slaveTransmitterMode,
                                        uint16_t timeout,
                                        uint8_t *value)
{
    if (slaveTransmitterMode == 0)
    {
        return HAL_I2C_Mem_Read(
            addr,
            reg,
            I2C_MEMADD_SIZE_8BIT,
            value,
            numBytesToRead,
            timeout);
    }
    else
    {
        return HAL_I2C_Master_Receive(addr,
                                      value,
                                      numBytesToRead,
                                      timeout);
    }
}

static HAL_StatusTypeDef I2Cx_WriteBytes(uint8_t addr,
                                         uint16_t reg,
                                         uint16_t numBytesToWrite,
                                         uint16_t timeout,
                                         uint8_t *value)
{

    return HAL_I2C_Mem_Write(addr,
                             reg,
                             I2C_MEMADD_SIZE_8BIT,
                             value,
                             numBytesToWrite,
                             timeout);
}

#endif /* HAL_I2C_MODULE_ENABLED_ALT1250 */

void WE_Delay(uint32_t Delay)
{
    HAL_Delay(Delay);
}

uint32_t WE_GetTick()
{
    return HAL_GetTick();
}

void WE_DelayMicroseconds(uint32_t sleepForUsec)
{
    WE_Delay(((sleepForUsec + 500) / 1000));
}

uint32_t WE_GetTickMicroseconds()
{
    uint32_t tickAmount = HAL_GetTick();
    return tickAmount * 1000;
}

void WE_UART_RXPin0_TXPin1_Transmit(const char *data, uint16_t dataLength)
{
    HAL_UART_RXPin0_TXPin1_Transmit(data, dataLength);
}


void WE_DEBUG_PRINT(char *data)
{
    printf(data);
}

bool WE_InitPins(WE_Pin_t pins[], uint8_t numPins)
{
    return true; 
}
bool WE_SetPin(WE_Pin_t pin, WE_Pin_Level_t out)
{
    return true; 
}

void WE_UART_RXPin0_TXPin1_Init(uint32_t baudrate,
                                WE_FlowControl_t fc,
                                WE_Parity_t par)
{
    HAL_UART__Internal_Initialize();
}

#ifdef HAL_SPI_MODULE_ENABLED_ALT1250
/**
 * @brief Reads bytes from SPI.
 * @param[in] chipSelectPin Pin used for chip select
 * @param[in] reg Register address
 * @param[in] numBytesToRead Number of bytes to read
 * @param[in] timeout Timeout for read operation
 * @param[out] value Pointer to data buffer
 * @retval HAL status
 */
static HAL_StatusTypeDef SPIx_ReadBytes(uint16_t chipSelectPin,
                                        uint8_t reg,
                                        uint16_t numBytesToRead,
                                        uint16_t timeout,
                                        uint8_t *value)
{
    /* TODO */
    return WE_SUCCESS;

    // HAL_StatusTypeDef status = HAL_OK;
    // HAL_GPIO_WritePin(chipSelectPort, chipSelectPin, GPIO_PIN_RESET);
    // /* Bit 7 has to be 0 for write and 1 for read operations */
    // uint8_t header = reg | (1 << 7);
    // /* For some sensors (e.g. HIDS) Bit 6 is used for auto-increment (MS) in multiple reads/writes (1: enabled, 0: disabled) */
    // //  if (numBytesToRead > 1)
    // //  {
    // //    header |= 1 << 6;
    // //  }
    // status = HAL_SPI_Transmit(handle, &header, 1, timeout);
    // if (status != HAL_OK)
    // {
    //     return status;
    // }
    // status = HAL_SPI_Receive(handle, value, numBytesToRead, timeout);
    // HAL_GPIO_WritePin(chipSelectPort, chipSelectPin, GPIO_PIN_SET);
    // return status;
}

/**
 * @brief Writes bytes to SPI.
 * @param[in] chipSelectPin Pin used for chip select
 * @param[in] reg The target register address to write
 * @param[in] numBytesToWrite Number of bytes to write
 * @param[in] timeout Timeout for write operation
 * @param[in] value The target register value to be written
 * @retval HAL status
 */
static HAL_StatusTypeDef SPIx_WriteBytes(uint16_t chipSelectPin,
                                         uint8_t reg,
                                         uint16_t numBytesToWrite,
                                         uint16_t timeout,
                                         uint8_t *value)
{
    /* TODO */
    return WE_SUCCESS;

    // HAL_StatusTypeDef status = HAL_OK;
    // HAL_GPIO_WritePin(chipSelectPort, chipSelectPin, GPIO_PIN_RESET);
    // /* Bit 7 has to be 0 for write and 1 for read operations */
    // uint8_t header = reg & ~(1 << 7);
    // /* For some sensors (e.g. HIDS) Bit 6 is used for auto-increment (MS) in multiple reads/writes (1: enabled, 0: disabled) */
    // //  if (numBytesToWrite > 1)
    // //  {
    // //    header |= 1 << 6;
    // //  }
    // status = HAL_SPI_Transmit(handle, &header, 1, timeout);
    // if (status != HAL_OK)
    // {
    //     return status;
    // }
    // status = HAL_SPI_Transmit(handle, value, numBytesToWrite, timeout);
    // HAL_GPIO_WritePin(chipSelectPort, chipSelectPin, GPIO_PIN_SET);
    // return status;
}

#endif /* HAL_SPI_MODULE_ENABLED_ALT1250 */
