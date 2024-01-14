#include "HAL/HAL.h"

static void SetValue(uint16_t value)
{
  digitalWrite(CONFIG_LED_STCP, LOW);
  shiftOut(CONFIG_LED_DS, CONFIG_LED_SHCP, MSBFIRST, value / 256);
  shiftOut(CONFIG_LED_DS, CONFIG_LED_SHCP, MSBFIRST, value % 256);
  digitalWrite(CONFIG_LED_STCP, HIGH);
}

void HAL::Led_Init()
{
  pinMode(CONFIG_LED_SHCP, OUTPUT);
  pinMode(CONFIG_LED_STCP, OUTPUT);
  pinMode(CONFIG_LED_DS, OUTPUT);
  digitalWrite(CONFIG_LED_STCP,LOW);

  SetValue(0x0);
}



void HAL::Led_SetValue(const Led_Info_t* value)
{
  SetValue(value->data);
}
