#include "Web.h"
#include "HAL/HAL.h"

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest* request) 
{
  request->send(404, "text/plain", "Not found");
}

TaskHandle_t handleTaskWeb;
void TaskWebStart(void* parameter)
{
  while (WiFi.isConnected() == false)
  {
    delay(1000);
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/plain", VERSION_FIRMWARE_NAME  " " VERSION_AUTHOR_NAME " " VERSION_SOFTWARE);
  });
  
  server.onNotFound(notFound);
  server.begin();
  Serial.println("WebServer Start.");

  vTaskDelete(handleTaskWeb);
}

void Web::Init()
{
  xTaskCreate(
    TaskWebStart,
    "WebThread",
    20000,
    nullptr,
    TASK_WEB_PRIORITIES,
    &handleTaskWeb
  );
}