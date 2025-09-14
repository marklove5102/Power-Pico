#include "gate.h"
#include "usart.h"
#include "math.h"

uint8_t gate_status = HIGH_CUR; // Default status

void Gate_Port_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(EN1_PORT, EN1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN2_PORT, EN2_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = EN1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EN1_PORT, &GPIO_InitStruct);

	/*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = EN2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EN2_PORT, &GPIO_InitStruct);
}

void flow_route_selection(uint8_t selection)
{
  if(selection > HIGH_CUR)
    selection = HIGH_CUR; // Invalid selection
  if(selection < LOW_CUR)
    selection = LOW_CUR;
	if(selection == HIGH_CUR)
  {
    HAL_GPIO_WritePin(EN1_PORT, EN1_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN2_PORT, EN2_PIN, GPIO_PIN_RESET);
  }
  else if(selection == MID_CUR)
  {
    HAL_GPIO_WritePin(EN1_PORT, EN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN2_PORT, EN2_PIN, GPIO_PIN_SET);
  }
  else if(selection == LOW_CUR)
  {
    HAL_GPIO_WritePin(EN1_PORT, EN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN2_PORT, EN2_PIN, GPIO_PIN_RESET);
  }
  gate_status = selection; // Update the status
}

uint8_t Gate_get_status(void)
{
  return gate_status;
}

// DMA中断中执行, 不能有阻塞
void Gate_Swich_and_UART_Send(ADC_Packet adc_packet)
{
  static uint8_t high_times = 0;
  static uint8_t low_times = 0;
  // low mid high
  uint16_t cur_adc = 0;
  switch(Gate_get_status()) {
    case LOW_CUR:
      cur_adc = adc_packet.data[0][1];
      break;
    case MID_CUR:
      cur_adc = adc_packet.data[0][2];
      break;
    case HIGH_CUR:
      cur_adc = adc_packet.data[0][3];
      break;
  }
  // 可信范围内
  if(cur_adc < ADC_TRUST_MAX) {
    adc_packet.header[3] = Gate_get_status();
    HAL_UART_Transmit_DMA(&huart6, (uint8_t*)&adc_packet, sizeof(adc_packet));
    // 计算电压电流值
    global_valtage = adc_packet.data[0][0] * 3.0f / 4096.0f * 11.0f; // 11 = (100+10)/10
    if(Gate_get_status() == LOW_CUR) {
      global_current = (adc_packet.data[0][1] - 2048) * (3.0f / 4096.0f / 50.0f / LOW_CUR_RES * 1000000.0f);
      global_cur_unit = UNIT_UA;
    }
    else if(Gate_get_status() == MID_CUR) {
      global_current = (adc_packet.data[0][2] - 2048) * (3.0f / 4096.0f / 50.0f / MID_CUR_RES * 1000.0f);
      global_cur_unit = UNIT_MA;
    }
    else if(Gate_get_status() == HIGH_CUR) {
      global_current = (adc_packet.data[0][3] - 2048) * (3.0f / 4096.0f / 50.0f / HIGH_CUR_RES * 1000.0f);
      global_cur_unit = UNIT_MA;
    }
    // 超过量程
    uint16_t diff = abs((int)cur_adc - 2048);
    if(diff > THRESH_HIGH) {
      high_times++;
      low_times = 0;
      if(high_times >= THRESH_TIMES) {
        high_times = 0;
        flow_route_selection(Gate_get_status()+1);
      }
    }
    else if(diff < THRESH_LOW) {
      low_times++;
      high_times = 0;
      if(low_times >= THRESH_TIMES) {
        low_times = 0;
        flow_route_selection(Gate_get_status()-1);
      }
    }
    else {
      high_times = 0;
      low_times = 0;
    }
  }
  // 不可信范围内
  else {
    flow_route_selection(Gate_get_status()+1);
  }
}
