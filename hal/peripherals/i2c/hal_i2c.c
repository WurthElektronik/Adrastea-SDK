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

#include "hal_common.h"

#ifdef ALT1250
#define MAX_I2C_DEVICES_QUANT (2)
#elif defined(ALT1255)
#define MAX_I2C_DEVICES_QUANT (1)
#else
#error No target platform specified!!
#endif

#define NONBLOCK_TX_FUNC_NAME "DRV_I2C_MasterTransmit_Nonblock"
#define NONBLOCK_RX_FUNC_NAME "DRV_I2C_MasterReceive_Nonblock"
#define BLOCK_TX_FUNC_NAME "DRV_I2C_MasterTransmit_Block"
#define BLOCK_RX_FUNC_NAME "DRV_I2C_MasterReceive_Block"

typedef DRV_I2C_Status (*i2cReceive)(Drv_I2C_Peripheral *i2c, uint32_t addr, const uint8_t *data,
                                     uint32_t num, bool xfer_pending);
typedef DRV_I2C_Status (*i2cTransmit)(Drv_I2C_Peripheral *i2c, uint32_t addr, const uint8_t *data,
                                      uint32_t num, bool xfer_pending);

osSemaphoreId_t i2c_sem_hal = NULL;
bool i2c_err_hal = false;
uint32_t i2c_event_hal[MAX_I2C_DEVICES_QUANT] = {0};
volatile I2C_BusId i2c_bus_id_hal = I2C_BUS_0;
static Drv_I2C_Peripheral *i2c_pripheral_hal[MAX_I2C_DEVICES_QUANT] = {0};

static i2cReceive local_receive = DRV_I2C_MasterReceive_Nonblock;
static char *local_receive_str = NONBLOCK_RX_FUNC_NAME;
static i2cTransmit local_transmit = DRV_I2C_MasterTransmit_Nonblock;
static char *local_transmit_str = NONBLOCK_TX_FUNC_NAME;
static I2C_OpMode opmode = OPMODE_NONBLOCK;



static void HAL_I2C__osSemaphoreCreate()
{
   if (!i2c_sem_hal)
   {
      i2c_sem_hal = osSemaphoreNew(1, 0, NULL);
   }
}


static void HAL_I2C__Initialize_EventCallBack(void *user_data, uint32_t event)
{
   if (event & (I2C_EVENT_TRANSACTION_INCOMPLETE | I2C_EVENT_TRANSACTION_ADDRNACK))
   {
      i2c_err_hal = true;
   }

   i2c_event_hal[(uint32_t)user_data] = event;
   osSemaphoreRelease(i2c_sem_hal);
}


uint8_t HAL_I2C__Initialize(void)
{
   Drv_I2C_EventCallback evt_cb;
   evt_cb.user_data = (void *)i2c_bus_id_hal;

   evt_cb.event_callback = HAL_I2C__Initialize_EventCallBack;
   DRV_I2C_Status ret = DRV_I2C_Initialize(i2c_bus_id_hal, &evt_cb, &i2c_pripheral_hal[i2c_bus_id_hal]);
}


uint8_t HAL__I2C_SetSpeed(uint32_t speed)
{
   DRV_I2C_Status ret = DRV_I2C_SetSpeed(i2c_pripheral_hal[i2c_bus_id_hal], speed);
   return ret;
}


uint8_t HAL__I2C_SetOpMode(uint8_t mode)
{
   if (mode < OPMODE_MAX)
   {
      opmode = (I2C_OpMode)mode;
      local_receive = opmode == OPMODE_NONBLOCK ? DRV_I2C_MasterReceive_Nonblock
                                                : DRV_I2C_MasterReceive_Block;
      local_receive_str =
          opmode == OPMODE_NONBLOCK ? NONBLOCK_RX_FUNC_NAME : BLOCK_RX_FUNC_NAME;
      local_transmit = opmode == OPMODE_NONBLOCK ? DRV_I2C_MasterTransmit_Nonblock
                                                 : DRV_I2C_MasterTransmit_Block;
      local_transmit_str =
          opmode == OPMODE_NONBLOCK ? NONBLOCK_TX_FUNC_NAME : BLOCK_TX_FUNC_NAME;
   }
   else
   {
      opmode = OPMODE_NONBLOCK;
      local_receive = DRV_I2C_MasterReceive_Nonblock;
      local_receive_str = NONBLOCK_RX_FUNC_NAME;
      local_transmit = DRV_I2C_MasterTransmit_Nonblock;
      local_transmit_str = NONBLOCK_TX_FUNC_NAME;
   }
}


uint8_t HAL_I2C__Set_I2C_Bus_Id(HAL_I2C_BusId busId)
{
   switch (busId)
   {
   case HAL_I2C_BusId_0:
      i2c_bus_id_hal = I2C_BUS_0;
      break;
   case HAL_I2C_BusId_1:
      i2c_bus_id_hal = I2C_BUS_1;
      break;
   default:
      i2c_bus_id_hal = I2C_BUS_0;
   }

   HAL_I2C__osSemaphoreCreate();

   return HAL_OK;
}


uint8_t HAL_I2C__SetPowerMode(HAL_I2C_PowerMode powerMode)
{
   DRV_I2C_Status ret = 0;

   switch (powerMode)
   {
   case HAL_I2C_POWER_OFF:
      ret = DRV_I2C_PowerControl(i2c_pripheral_hal[i2c_bus_id_hal], I2C_POWER_OFF);
      break;
   case HAL_I2C_POWER_FULL:
      ret = DRV_I2C_PowerControl(i2c_pripheral_hal[i2c_bus_id_hal], I2C_POWER_FULL);
      break;
   default:
      ret = DRV_I2C_PowerControl(i2c_pripheral_hal[i2c_bus_id_hal], I2C_POWER_FULL);
   }

   return ret;
}

uint8_t HAL_I2C__Uninitialize(void)
{
   DRV_I2C_Status ret = DRV_I2C_Uninitialize(i2c_bus_id_hal);
   return ret;
}


uint8_t HAL_I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
   DRV_I2C_Status ret;

   uint8_t RegisterAddress[128];

   uint32_t i;

   for (i = 0; i < (uint32_t)Size; i++)
   {
      RegisterAddress[i] = (uint8_t)(MemAddress >> (8 * (Size - i - 1)));
   }

   for (i = 0; i < Size; i++)
   {
      RegisterAddress[Size + i] = pData[i];
   }


   i2c_err_hal = false;

   ret = local_transmit(i2c_pripheral_hal[i2c_bus_id_hal], DevAddress, RegisterAddress, (uint32_t)Size + Size, false);

   if (ret == DRV_I2C_OK)
   {
      if (opmode == OPMODE_NONBLOCK
              ? (i2c_sem_hal && (osSemaphoreAcquire(i2c_sem_hal, osWaitForever) == osOK))
              : true)
      {
         if (opmode == OPMODE_NONBLOCK)
         {
            if (i2c_err_hal) return HAL_ERROR;
         }
      }
   }

   return ret;
}


uint8_t HAL_I2C_Mem_Read(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{

   DRV_I2C_Status ret;
   uint32_t address, num, n;
   uint8_t data[64] = {0}, value;
   uint8_t val = 160;
   uint8_t addrLen;
   char *param;

   uint8_t RegisterAddress[3];

   uint8_t i ;
      uint32_t dev_id = (uint32_t)(DevAddress | opmode);
   for (i = 0; i < (uint32_t)Size; i++)
   {
      RegisterAddress[i] = (uint8_t)(MemAddress >> (8 * (MemAddSize - i - 1)));
   }

   i2c_err_hal = false;
   ret = local_transmit(i2c_pripheral_hal[i2c_bus_id_hal], dev_id, RegisterAddress, (uint32_t)MemAddSize, true);
   if (ret == DRV_I2C_OK)
   {
      if (opmode == OPMODE_NONBLOCK
              ? (i2c_sem_hal && (osSemaphoreAcquire(i2c_sem_hal, osWaitForever) == osOK))
              : true)
      {
         if (opmode == OPMODE_NONBLOCK)
         {
            if (i2c_err_hal)
               return HAL_ERROR;

            uint32_t dev_id = (uint32_t)(DevAddress | opmode);
            ret = local_receive(i2c_pripheral_hal[i2c_bus_id_hal], dev_id, pData, Size, false);

            if (ret == DRV_I2C_OK)
            {
               if (opmode == OPMODE_NONBLOCK
                       ? (i2c_sem_hal && (osSemaphoreAcquire(i2c_sem_hal, osWaitForever) == osOK))
                       : true)
               {
                  if (opmode == OPMODE_NONBLOCK)
                  {
                     if (i2c_err_hal)
                        return HAL_ERROR;
                  }
               }
            }
         }
      }
   }


   return ret;
}


uint8_t HAL_I2C_Master_Receive(uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
   DRV_I2C_Status ret;
   
   ret = local_transmit(i2c_pripheral_hal[i2c_bus_id_hal],
                        DevAddress,
                        pData,
                        Size, true);

   return ret;
}


uint8_t HAL_I2C_IsDeviceReady(uint16_t DevAddress, uint32_t Trials, uint32_t Timeout)
{
   return HAL_OK;
}