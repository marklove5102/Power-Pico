/* Private includes -----------------------------------------------------------*/
//includes
#include "user_TasksInit.h"
#include "main.h"
#include "key.h"
#include "beep.h"
#include "BL24C02.h" // settings

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
			// beep
			if(Sys_Get_KeySoundEnable())
			{
				beep_open();
				osDelay(50);
				beep_close();
			}
		}
		osDelay(10);
	}
}
