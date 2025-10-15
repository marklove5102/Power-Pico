#ifndef __KEY_H__
#define __KEY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

// boot, yes, right, left, no
#define KEYB_NUM 1
#define KEYY_NUM 2
#define KEYL_NUM 3
#define KEYR_NUM 4
#define KEYN_NUM 5

//KEYB
#define KEYB_PORT	GPIOA
#define KEYB_PIN	GPIO_PIN_0
#define KEYB HAL_GPIO_ReadPin(KEYB_PORT,KEYB_PIN)

//KEYY
#define KEYY_PORT	GPIOA
#define KEYY_PIN	GPIO_PIN_4
#define KEYY HAL_GPIO_ReadPin(KEYY_PORT,KEYY_PIN)

//KEYL
#define KEYL_PORT	GPIOA
#define KEYL_PIN	GPIO_PIN_3
#define KEYL HAL_GPIO_ReadPin(KEYL_PORT,KEYL_PIN)

//KEYR
#define KEYR_PORT	GPIOA
#define KEYR_PIN	GPIO_PIN_2
#define KEYR HAL_GPIO_ReadPin(KEYR_PORT,KEYR_PIN)

//KEYN
#define KEYN_PORT	GPIOA
#define KEYN_PIN	GPIO_PIN_1
#define KEYN HAL_GPIO_ReadPin(KEYN_PORT,KEYN_PIN)

void Key_Port_Init(void);
uint8_t KeyScan(uint8_t mode);


#ifdef __cplusplus
}
#endif
#endif

