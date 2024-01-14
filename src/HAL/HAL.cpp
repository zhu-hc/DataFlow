#include "HAL/HAL.h"
#include "App/Configs/Version.h"
#include "lvgl.h"

#define DISP_HOR_RES         CONFIG_SCREEN_HOR_RES
#define DISP_VER_RES         CONFIG_SCREEN_VER_RES
#define DISP_BUF_SIZE        CONFIG_SCREEN_BUFFER_SIZE

extern lv_color_t* lv_disp_buf_p;

void HAL::Init()
{
    Serial.begin(115200);
    Serial.println(VERSION_FIRMWARE_NAME);
    Serial.println("Version: " VERSION_SOFTWARE);
    Serial.println("Author: " VERSION_AUTHOR_NAME);

    HAL::Power_Init();
    HAL::WiFi_Init();
    HAL::Clock_Init();
    HAL::Backlight_Init();
    HAL::Rgb_Init();
    HAL::Led_Init();
    HAL::SD_Init();
    HAL::Encoder_Init();
    HAL::Key_Init(); 
}

void HAL::Update()
{
    HAL::Power_Update();
    HAL::SD_Update();
    HAL::Key_Update();
}
