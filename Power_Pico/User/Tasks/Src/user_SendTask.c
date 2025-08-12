/* Private includes -----------------------------------------------------------*/
//includes
#include "user_TasksInit.h"
#include "main.h"

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
	while(1)
	{
    if(osMessageQueueGet(Key_MessageQueue, &keystr, NULL, 0)==osOK)
		{
      UART6_TX_Send((uint8_t *)"key pressed\r\n", 13);
    }
		osDelay(1);
	}
}
