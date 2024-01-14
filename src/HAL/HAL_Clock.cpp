#include "HAL/HAL.h"


void HAL::Clock_Init()
{
  Clock_Info_t info = {
    .year = 2024,
    .month = 1,
    .day = 1,
    .hour = 8,
    .minute = 0,
    .second = 0
  };
  Clock_SetInfo(&info);
}

void HAL::Clock_GetInfo(Clock_Info_t* info)
{
  struct tm time;
  if (getLocalTime(&time))
  {
    info->year = time.tm_year;
    info->month = time.tm_mon;
    info->day = time.tm_mday;
    info->week = time.tm_wday;
    info->hour = time.tm_hour;
    info->minute = time.tm_min;
    info->second = time.tm_sec;
  }
}

void HAL::Clock_SetInfo(const Clock_Info_t* info)
{
  struct tm t = {0};
  t.tm_year = info->year - 1900;  
  t.tm_mon = info->month - 1;
  t.tm_mday = info->day;
  t.tm_hour = info->hour;
  t.tm_min = info->minute;
  t.tm_sec = info->second;
  time_t timeSinceEpoch = mktime(&t);
  struct timeval now = { .tv_sec = timeSinceEpoch };
  settimeofday(&now, NULL);
}

void HAL::Clock_NTP()
{
  configTime(8 * 3600, 0, "ntp.aliyun.com");
  Serial.println("Clock_NTP.");
}
