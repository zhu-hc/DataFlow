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
  
  server.on("/GetConfig", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if (!request->hasParam("Name")) 
    {
      request->send(400, "text/plain", "Not Found Name");
      return;
    }
    if (!request->hasParam("Config")) 
    {
      request->send(400, "text/plain", "Not Found Config");
      return;
    }
    String name = request->getParam("Name")->value();
    String config = request->getParam("Config")->value();
    HAL::Config_Info_t info;
    info.Name = config;
    if (HAL::FFS_ReadConfig(name, &info) == true)
      request->send(200, "text/plain", name + "." + config + " = " + info.Value);
    else
      request->send(400, "text/plain", name + "." + config + " Not Found");
  });

  server.on("/SetConfig", HTTP_POST, [](AsyncWebServerRequest *request){
    if (!request->hasParam("Name")) 
    {
      request->send(400, "text/plain", "Not Found Name");
      return;
    }
    if (!request->hasParam("Config")) 
    {
      request->send(400, "text/plain", "Not Found Config");
      return;
    }
    if (!request->hasParam("Value")) 
    {
      request->send(400, "text/plain", "Not Found Value");
      return;
    }
    String name = request->getParam("Name")->value();
    String config = request->getParam("Config")->value();
    String value = request->getParam("Value")->value();
    HAL::Config_Info_t info;
    info.Name = config;
    info.Value = value;
    if (HAL::FFS_WriteConfig(name, &info) == true)
      request->send(200, "text/plain", name + "." + config + " Success.");
    else
      request->send(400, "text/plain", name + "." + config + " Fail.");
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