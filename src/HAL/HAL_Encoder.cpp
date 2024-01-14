#include "HAL/HAL.h"

static volatile int16_t EncoderDiff = 0;

static void Encoder_IrqHandler()
{
  static volatile int count, countLast;
  static volatile uint8_t a0, b0;
  static volatile uint8_t ab0;
  uint8_t a = digitalRead(CONFIG_ENCODER_RIGHT_A_PIN);
  uint8_t b = digitalRead(CONFIG_ENCODER_RIGHT_B_PIN);
  if (a != a0)
  {
    a0 = a;
    if (b != b0)
    {
      b0 = b;
      count += ((a == b) ? 1 : -1);
      if ((a == b) != ab0)
      {
        count += ((a == b) ? 1 : -1);
      }
      ab0 = (a == b);
    }
  }

  if (count != countLast)
  {
    EncoderDiff += (count - countLast) > 0 ? 1 : -1;
    countLast = count;
  }
}

void HAL::Encoder_Init()
{
  pinMode(CONFIG_ENCODER_RIGHT_A_PIN, INPUT_PULLUP);
  pinMode(CONFIG_ENCODER_RIGHT_B_PIN, INPUT_PULLUP);
  pinMode(CONFIG_ENCODER_RIGHT_PUSH_PIN, INPUT_PULLUP);

  attachInterrupt(CONFIG_ENCODER_RIGHT_A_PIN, Encoder_IrqHandler, CHANGE);
}

int16_t HAL::Encoder_GetDiff()
{
  int16_t diff = EncoderDiff / 2;
  if (diff != 0)
  {
    // EncoderDiff是实际的脉冲数；把本次变量用掉了，需要重新置0
    EncoderDiff = 0;
  }
  
  return diff;
}

bool HAL::Encoder_GetIsPush()
{
  return (digitalRead(CONFIG_ENCODER_RIGHT_PUSH_PIN) == LOW);
}
