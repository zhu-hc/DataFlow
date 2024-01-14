#ifndef __HAL_H
#define __HAL_H

#include <Arduino.h>
#include "HAL_Def.h"
#include "App/Configs/Config.h"
#include "CommonMacro.h"
#include "FreeRTOS.h"
#include <FastLED.h>

namespace HAL
{
    typedef bool (*CommitFunc_t)(void* info, void* userData);

    void Init();
    void Update();

    /* Clock */
    void Clock_Init();
    void Clock_GetInfo(Clock_Info_t* info);
    void Clock_SetInfo(const Clock_Info_t* info);
    void Clock_NTP();

    /* Backlight */
    void Backlight_Init();
    uint32_t Backlight_GetValue();
    void Backlight_SetValue(int32_t val);
    void Backlight_SetGradual(uint32_t target, uint16_t time = 500);
    void Backlight_ForceLit(bool en);

    /* Rgb */
    void Rgb_Init();
    void Rgb_SetBrightness(uint8_t scale);
    void Rgb_Fill(uint8_t id, CRGB value);
    void Rgb_SetState(const Rgb_Info_t* info);

    /** Led **/
    void Led_Init();
    void Led_SetValue(const Led_Info_t* value);

    /* Encoder */
    void Encoder_Init();
    int16_t Encoder_GetDiff();
    bool Encoder_GetIsPush();

    /* Key */
    void Key_Init();
    void Key_Update();
    void Key_SetCommitCallback(CommitFunc_t func, void* userData);

    /* Power */
    void Power_Init();
    void Power_Update();
    void Power_GetInfo(Power_Info_t* const info);
    typedef void(*Power_CallbackFunction_t)(void);
    void Power_SetEventCallback(Power_CallbackFunction_t callback);

    /* SD */
    bool SD_Init();
    void SD_Update();
    bool SD_GetReady();
    uint32_t SD_GetSizeMB();
    const char* SD_GetTypeName();
    void SD_GetInfo(Storage_Info_t* const info);
    typedef void(*SD_CallbackFunction_t)(bool insert);
    void SD_SetEventCallback(SD_CallbackFunction_t callback);

    /* WiFi */
    void WiFi_Init();
    void WiFi_GetInfo(WiFi_Info_t* const info);

    /* SPIFFS */
    void FFS_Init();
}

#endif
