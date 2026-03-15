/* Private includes -----------------------------------------------------------*/
//includes
#include "adc.h"
#include "user_TasksInit.h"
#include "user_MessageTask.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"
#include "BL24C02.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  task for receiving messages, such as USB update requests.
  * @param  argument: Not used
  * @retval None
  */
void MessageReceiveTask(void *argument)
{
	while(1)
	{
    if(get_update_request()) {

      // clear the flag
      set_update_request(false);
      // set the EEPROM flag
      EEPROM_UpdateCommand_Write(true);
      HAL_Delay(100);
      USER_USB_DEVICE_DeInit();
      // 给予PC足够的时间来识别设备断开
      HAL_Delay(500);
      // reset
      NVIC_SystemReset();
    }
		osDelay(500);
	}
}

/**
 * @brief  send adc data to PC via USB,
 * @param  argument: Not used
 */
void MessageSendTask(void *argument)
{
  uint32_t flags;
  while (1)
  {
    // 1. 等待两个标志中的任意一个 (osFlagsWaitAny)
    flags = osThreadFlagsWait(FLAG_ADC_HALF_READY | FLAG_ADC_FULL_READY,
                              osFlagsWaitAny,
                              osWaitForever);

    // 2. 判断是不是出错了 (比如超时或者传参错误，通常返回值最高位会置1)
    if (flags & 0x80000000) {
        continue; // 错误处理
    }

    // 3. 检查具体是哪个标志位被置位了，然后处理对应的数据
    if (flags & FLAG_ADC_HALF_READY)
    {
        Process_ADC_Chunk(&adc_raw_buffer[0][0], 0);
    }

    if (flags & FLAG_ADC_FULL_READY)
    {
        Process_ADC_Chunk(&adc_raw_buffer[ADC_TIMES][0], 1);
    }
  }
}
