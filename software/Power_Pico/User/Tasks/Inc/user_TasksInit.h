#ifndef __USER_TASKSINIT_H__
#define __USER_TASKSINIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "cmsis_os.h"

// 定义一个标志位，表示 ADC 数据已经准备好，可以发送了
#define FLAG_ADC_HALF_READY  0x0001U  // 0000 0001
#define FLAG_ADC_FULL_READY  0x0002U  // 0000 0010

extern osThreadId_t MessageSendTaskHandle; // 用于发送 ADC 数据的任务句柄

extern osMessageQueueId_t Key_MessageQueue;
extern osMessageQueueId_t PD_cmd_MessageQueue;
extern osMessageQueueId_t PD_handle_event_MsgQueue;

void User_Tasks_Init(void);
void TaskTickHook(void);

#ifdef __cplusplus
}
#endif

#endif

