#include "HAL/HAL.h"

static CRGB rgb[CONFIG_RGB_NUM][CONFIG_RGB_LEDS];
static CRGB color[CONFIG_RGB_NUM] = { CRGB::Black, CRGB::Black };
static Rgb_State_t state[CONFIG_RGB_NUM] = { Off, Off };
static uint32_t data[CONFIG_RGB_NUM] = { 100, 100 };

static void fadeToBlack(CRGB *leds, int16_t num_leds, uint8_t fadeBy)
{
  int temp = 255;
  for (int i = num_leds; i > num_leds - CONFIG_RGB_LEDS; i--)
  {
    leds[i < 0 ? i + CONFIG_RGB_LEDS : i].nscale8(temp);
    temp = temp < fadeBy ? 0 : temp - fadeBy;
  }
}

static void control(CRGB *leds, Rgb_State_t state, uint8_t data, CRGB color, uint8_t cnt)
{
  if (state == Off)
  {
    for (int i = 0; i < CONFIG_RGB_LEDS; i++) leds[i] = CRGB::Black;
  }
  else if (state == On)
  {
    for (int i = 0; i < CONFIG_RGB_LEDS; i++) leds[i] = color;
  }
  else if (state == Flow)
  {
    for (int i = 0; i < CONFIG_RGB_LEDS; i++) leds[i] = color;
    fadeToBlack(leds, cnt, CONFIG_RGB_FADE);

    delay(data);
  }
  else if (state == Part)
  {
    for (int i = 0; i < CONFIG_RGB_LEDS; i++)  leds[i] = i < data ? color : CRGB::Black;
  }
}

TaskHandle_t handleTaskRgb0;
void TaskRgb0Update(void* parameter)
{
  static uint8_t cnt = 0;
  for (;;)
  {
    control(rgb[0], state[0], data[0], color[0], cnt);

    FastLED.show();
    delay(50);
    if (++cnt >= CONFIG_RGB_LEDS) cnt = 0;
  }
}

TaskHandle_t handleTaskRgb1;
void TaskRgb1Update(void* parameter)
{
  static uint8_t cnt = 0;
  for (;;)
  {
    control(rgb[1], state[1], data[1], color[1], cnt);

    FastLED.show();
    delay(50);
    if (++cnt >= CONFIG_RGB_LEDS) cnt = 0;
  }
}

void HAL::Rgb_Init()
{
  FastLED.addLeds<WS2812B, CONFIG_RGB_S0, GRB>(rgb[0], CONFIG_RGB_LEDS);
  FastLED.addLeds<WS2812B, CONFIG_RGB_S1, GRB>(rgb[1], CONFIG_RGB_LEDS);
  FastLED.setCorrection(TypicalLEDStrip);
  Rgb_SetBrightness(20);

  xTaskCreate(
    TaskRgb0Update,
    "Rgb0Thread",
    8096,
    nullptr,
    TASK_RGB_PRIORITIES,
    &handleTaskRgb0
  );

  xTaskCreate(
    TaskRgb1Update,
    "Rgb1Thread",
    8096,
    nullptr,
    TASK_RGB_PRIORITIES,
    &handleTaskRgb1
  );
}

void HAL::Rgb_SetBrightness(uint8_t scale)
{
  FastLED.setBrightness(scale);
}

void HAL::Rgb_Fill(uint8_t id, CRGB value)
{
  id = id % CONFIG_RGB_NUM;
  for (int i = 0; i < CONFIG_RGB_LEDS; i++) rgb[id][i] = value;
  FastLED.show();
}

void HAL::Rgb_SetState(const Rgb_Info_t* info)
{
  if (info->id >= CONFIG_RGB_NUM) return;

  color[info->id] = CRGB(info->r, info->g, info->b);
  state[info->id] = info->state;
  data[info->id] = info->data;
}
