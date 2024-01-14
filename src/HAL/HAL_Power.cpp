#include "HAL.h"

#define BATT_MAX_VOLTAGE    3900
#define BATT_MIN_VOLTAGE    3300

static volatile uint16_t Power_ADCValue = 0;
static uint16_t Power_ADCValue_last[10] = {4095};
static HAL::Power_CallbackFunction_t EventCallback;

static void Power_ADC_TrigUpdate()
{
    Power_ADCValue = analogRead(CONFIG_BAT_DET_PIN);
}

void HAL::Power_Init()
{
  pinMode(CONFIG_POWER_CHK, INPUT);
  pinMode(CONFIG_USB_CHK, INPUT);
  pinMode(CONFIG_BAT_DET_PIN, INPUT);
  pinMode(CONFIG_BAT_CHG_DET_PIN, INPUT_PULLUP);
  pinMode(CONFIG_POWER_HOLD, OUTPUT);
  digitalWrite(CONFIG_POWER_HOLD, HIGH);

  Serial.println("Power: ON");
}

void HAL::Power_Update()
{
  CM_EXECUTE_INTERVAL(Power_ADC_TrigUpdate(), 1000);

  if (!digitalRead(CONFIG_POWER_CHK))
  {
    Serial.println("Power: OFF");
    if (EventCallback) EventCallback();
    Backlight_SetGradual(0, 500);
    delay(500);
    digitalWrite(CONFIG_POWER_HOLD, LOW);
  }
}

void HAL::Power_GetInfo(Power_Info_t* const info)
{
  uint32_t sum = Power_ADCValue;
  for (int i = 9; i > 0; i--)
  {
      Power_ADCValue_last[i] = Power_ADCValue_last[i - 1];
      sum += Power_ADCValue_last[i - 1];
  }
  Power_ADCValue_last[0] = Power_ADCValue;
  int voltage = map(
    sum / 10,
    0, 4095,
    0, 3300
  );
  voltage *= 2;

  CM_VALUE_LIMIT(voltage, BATT_MIN_VOLTAGE, BATT_MAX_VOLTAGE);

  int usage = map(
    voltage,
    BATT_MIN_VOLTAGE, BATT_MAX_VOLTAGE,
    0, 100
  );

  info->usage = usage;
  info->isCharging = usage != 100 && !digitalRead(CONFIG_BAT_CHG_DET_PIN);
  info->isExPower = digitalRead(CONFIG_USB_CHK);
  info->voltage = voltage;
}

void HAL::Power_SetEventCallback(Power_CallbackFunction_t callback)
{
  EventCallback = callback;
}
