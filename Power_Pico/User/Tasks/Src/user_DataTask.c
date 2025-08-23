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
    
		osDelay(1);
	}
}
