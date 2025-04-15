
#include "hal_common.h"
#include "hal_helper.h"
#include "hal_uart.h"

static serial_handle Adrastea_Internal_Serial_Handler = NULL; /*  Modem UART Handler              */
static serial_handle Adrastea_External_Serial_Handler = NULL; /*  Serial UART Handler             */

TaskHandle_t Internal_Uart_Task_Handler = NULL;

static uint32_t console_write(char *buf, uint32_t len)
{
  if (!Adrastea_External_Serial_Handler)
  {
    return 0;
  }

  printf("%.*s", (int)len, buf);
  return len;
}

static void HAL_Internal_Uart__Task(void *pvParameters)
{

  char c;

  while (1)
  {
    serial_read(Adrastea_Internal_Serial_Handler, &c, 1);
    WE_UART_RXPin0_TXPin1_HandleRxByte(c);
    console_write(&c, 1);
  }
}

void HAL_UART_RXPin0_TXPin1_Transmit(const char *data, uint16_t dataLength)
{

  /* Create Internal UART Handler if not exist .*/
  if (!Adrastea_Internal_Serial_Handler)
  {
    Adrastea_Internal_Serial_Handler = serial_open(ADRASTEA_INTERNAL_UART);
  }
  serial_write(Adrastea_Internal_Serial_Handler, data, dataLength);
}

uint32_t HAL_External_UART_Read(char *buf, uint32_t len)
{
  return serial_read(Adrastea_External_Serial_Handler, buf, len);
}

uint32_t HAL_Internal_UART_Read(char *buf, uint32_t len)
{
  return serial_read(Adrastea_Internal_Serial_Handler, buf, len);
}

void HAL_Write_Internal_Uart(char *paramBuffer)
{
  serial_write(Adrastea_Internal_Serial_Handler, paramBuffer, strlen(paramBuffer));
}

void HAL_Write_External_Uart(char *paramBuffer)
{

  /* Create External UART Handler if not exist .*/
  if (!Adrastea_External_Serial_Handler)
  {
    Adrastea_External_Serial_Handler = serial_open(ADRASTEA_EXTERNAL_UART);
  }

  serial_write(Adrastea_External_Serial_Handler, paramBuffer, strlen(paramBuffer));
}

int32_t HAL_Start_Internal_UART_Communication(void)
{
  return 0;
}

int HAL_UART__External_Initialize(void)
{
  return 0;
}

int HAL_UART__Internal_Initialize(void)
{
  Adrastea_Internal_Serial_Handler = serial_open(ADRASTEA_INTERNAL_UART);
  Adrastea_External_Serial_Handler = serial_open(ADRASTEA_EXTERNAL_UART);

  /*Set the external serial port as standart output*/
  newlib_set_stdout_port(ADRASTEA_EXTERNAL_UART);

  printf("UART Connection between Application MCU to Host MCU is setup\r\n");

  xTaskCreate(HAL_Internal_Uart__Task,      /* The function that implements the task. */
              "Internal_Uart_Task_",        /* The text name assigned to the task - for debug only as it is not used by the kernel. */
              configMINIMAL_STACK_SIZE * 2, /* The size of the stack to allocate to the task. */
              (void *)NULL,                 /* The parameter passed to the task */
              configMAX_PRIORITIES - 2,     /* The priority assigned to the task - minimal priority. */
              &Internal_Uart_Task_Handler);

  return 0;
}

serial_handle HAL_Get_Internal_Uart_Handler(void)
{
  return Adrastea_Internal_Serial_Handler;
}

serial_handle HAL_Get_External_Uart_Handler(void)
{
  return Adrastea_External_Serial_Handler;
}
