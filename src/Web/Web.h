#ifndef __WEB_H
#define __WEB_H

#include "App/Configs/Config.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

namespace Web
{
  void Init();
}

#endif