/* Private includes -----------------------------------------------------------*/
//includes
#include "user_TasksInit.h"
#include "user_PDUFPTask.h"
#include "main.h"
#include "fusb302_dev.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  task for PD_UFP
  * @param  argument: Not used
  * @retval None
  */
void PDUFPTask(void *argument)
{
  // FUSB init
  fusb302_dev_init();
  // set
  PD_protocol_set_power_option(&app_pd.protocol, PD_POWER_OPTION_MAX_9V);
  PD_protocol_set_PPS(&app_pd.protocol, PPS_V(6.0), PPS_A(2.0), false);
	while(1)
	{
    if (fusb302_timer() || HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET) {
        FUSB302_event_t FUSB302_events = 0;
        for (uint8_t i = 0; i < 3 && FUSB302_alert(&fusb302_dev, &FUSB302_events) != FUSB302_SUCCESS; i++) {}
        if (FUSB302_events) {
            handle_FUSB302_event(FUSB302_events);
        }
    }
		osDelay(1);
	}
}
