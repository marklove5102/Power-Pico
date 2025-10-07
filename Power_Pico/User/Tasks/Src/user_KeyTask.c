/* Private includes -----------------------------------------------------------*/
//includes
#include "user_TasksInit.h"
#include "main.h"
#include "key.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  Key press check task
  * @param  argument: Not used
  * @retval None
  */
void KeyTask(void *argument)
{
	uint8_t keystr = 0;
	while(1)
	{
		keystr = KeyScan(0);
		if(keystr != 0)
		{
			osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
		}
		osDelay(10);
	}
}
