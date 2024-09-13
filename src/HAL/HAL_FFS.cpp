#include "HAL/HAL.h"

static inline String CONFIG_NAME(String name)
{
  return "/" + name + ".cfg";
}

JsonDocument doc;

void HAL::FFS_Init()
{
  // 初始化 SPIFFS
  if (!SPIFFS.begin(true)) 
  {
    Serial.println("FFS Init Fail.");
    return;
  }

  Serial.println("FFS Init Done.");
}

bool HAL::FFS_WriteConfig(String app, const Config_Info_t * const info)
{
  Serial.println("WriteConfig " + app + ": " + info->Name + " = " + info->Value);

  File file;
  String str;
  if (SPIFFS.exists(CONFIG_NAME(app)))
  {
    file = SPIFFS.open(CONFIG_NAME(app), FILE_READ);
    if (!file) return false;

    str = file.readString();
    deserializeJson(doc, str);
  }
  else
  {
    doc.clear();
  }

  file.close();
  file = SPIFFS.open(CONFIG_NAME(app), FILE_WRITE);
  if (!file) return false;
  doc[info->Name] = info->Value;
  serializeJson(doc, str);
  file.println(str);

  doc.clear();
  file.close();
  return true;
}

bool HAL::FFS_ReadConfig(String app, Config_Info_t * const info)
{
  File file;
  String str;
  if (!SPIFFS.exists(CONFIG_NAME(app)))
  {
    return false;
  }
  file = SPIFFS.open(CONFIG_NAME(app), FILE_READ);
  if (!file) return false;
  str = file.readString();
  deserializeJson(doc, str);

  if (doc[info->Name].isNull()) return false;

  info->Value = doc[info->Name].as<String>();
  Serial.println("ReadConfig " + app + ": " + info->Name + " = " + info->Value);
  return true;
}
