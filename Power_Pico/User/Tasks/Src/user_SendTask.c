/* Private includes -----------------------------------------------------------*/
//includes
#include "user_TasksInit.h"
#include "main.h"
#include "adc.h"
#include "gate.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  task for send messages or data
  * @param  argument: Not used
  * @retval None
  */
void UartSendTask(void *argument)
{
  uint8_t keystr = 0;
  uint16_t cur_bias = 4096 / 2;
	while(1)
	{
    if(osMessageQueueGet(Key_MessageQueue, &keystr, NULL, 0)==osOK)
		{
      // UART6_TX_Send((uint8_t *)"key pressed\r\n", 13);
    }
    // send protocol frame
    for(int i = 0 ; i < ADC_TIMES ; i++)
    {
      // direct & unit
      uint8_t dir_unit = 0x00; // positive, uA
      uint8_t unit = Gate_get_status(); // 0 - low current, 1 - mid current, 2 - high current
      dir_unit |= (unit & 0x0F); // unit
      // current
      uint32_t cur;
      // voltage *100times
      uint32_t volt = adc_buf[i][3] * 3 * 100 / 4096; // 12bit ADC, 0-4095
      // cur direction and value
      if(adc_buf[i][2-unit] > cur_bias) {
        dir_unit |= 0x10; // negative
        // cur *100times
        cur = (adc_buf[i][2-unit] - cur_bias) * 3 * 100 / 4096; // 3.0 Vref, 100 times, 12bit ADC
      }
      else {
        // cur *100times
        cur = (cur_bias - adc_buf[i][2-unit]) * 3 * 100 / 4096; // 3.0 Vref, 100 times, 12bit ADC
      }
      // protocol frame
      uint8_t protocol_frame[9] = {0x55, 0xAA, dir_unit, (cur<<8 & 0xff), (cur & 0xff), (volt<<8 & 0xff), (volt & 0xff), 0xAA, 0x55};
      UART6_TX_Send(protocol_frame, sizeof(protocol_frame));
    }
		osDelay(1);
	}
}
