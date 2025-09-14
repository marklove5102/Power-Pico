/* Private includes -----------------------------------------------------------*/
//includes
#include "user_TasksInit.h"
#include "user_DataTask.h"
#include "main.h"
#include "adc.h"
#include "gate.h"
#include "usart.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  task for data process and so on
  * @param  argument: Not used
  * @retval None
  */
void DataTask(void *argument)
{
  uint8_t keystr = 0;
  uint16_t cur_bias = 4096 / 2;
	while(1)
	{
    if(osMessageQueueGet(Key_MessageQueue, &keystr, NULL, 0)==osOK)
		{
      // UART6_TX_Send((uint8_t *)"key pressed\r\n", 13);

    }
    // __disable_irq();
    // if(adc_buf_index == 0)
    //   memcpy((uint16_t*)adc_packet.data, (uint16_t*)ADC_BUF[1], sizeof(adc_packet.data));
    // else
    //   memcpy((uint16_t*)adc_packet.data, (uint16_t*)ADC_BUF[0], sizeof(adc_packet.data));
    // __enable_irq();
    // adc_packet.header[0] = 0x55;
    // adc_packet.header[1] = 0xAA;
    // adc_packet.header[2] = ADC_TIMES;
    // adc_packet.header[3] = ADC_CHANELS;
    // adc_packet.header[4] = 0x10;
    // HAL_UART_Transmit_DMA(&huart6, (uint8_t *)&adc_packet, sizeof(adc_packet));
		osDelay(1);
	}
}
