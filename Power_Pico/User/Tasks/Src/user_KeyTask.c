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
		switch(keystr)
		{
			case KEYB_NUM:
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
				break;

			case KEYY_NUM:
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
				break;

			case KEYL_NUM:
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
				break;

			case KEYR_NUM:
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
				break;

			case KEYN_NUM:
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
				break;
		}
		osDelay(1);
	}
}
