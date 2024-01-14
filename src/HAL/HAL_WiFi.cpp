#include "HAL/HAL.h"
#include <WiFiManager.h>

static WiFiManager wm;

TaskHandle_t handleTaskWiFi;
void TaskWiFiUpdate(void* parameter)
{
  delay(1000);

  wm.setAPStaticIPConfig(IPAddress(192,168,1,1), IPAddress(192,168,1,1), IPAddress(255,255,255,0));
  if (!wm.autoConnect("AutoConnectAP"))
  {
    Serial.println("Failed to connect WiFi.");
  }
  vTaskDelete(handleTaskWiFi);
}

void HAL::WiFi_Init()
{
  xTaskCreate(
    TaskWiFiUpdate,
    "LvglThread",
    20000,
    nullptr,
    TASK_WIFI_PRIORITIES,
    &handleTaskWiFi
  );
}

void HAL::WiFi_GetInfo(WiFi_Info_t* const info)
{
  info->isConnected = WiFi.isConnected();
  info->SSID = WiFi.SSID();
  info->IP = WiFi.localIP().toString();
  info->RSSI = WiFi.RSSI();
}
