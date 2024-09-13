#ifndef __HAL_DEF_H
#define __HAL_DEF_H

#include <Arduino.h>

#define HAL_RGB0      0
#define HAL_RGB1      1

typedef enum 
{
    Off,
    On,
    Flow,
    Part
} Rgb_State_t;

typedef enum 
{
    Left,
    Right
} Key_Value_t;

typedef enum 
{
    Front,
    Rear
} Led_Value_t;

namespace HAL
{

/* Clock */
typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} Clock_Info_t;

/* Rgb */
typedef struct
{
    uint8_t id;
    Rgb_State_t state;
    uint8_t data;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Rgb_Info_t;

/* Led */
typedef struct
{
    Led_Value_t led;
    uint16_t data;
} Led_Info_t;

/* Power */
typedef struct
{
    uint16_t voltage;
    uint8_t usage;
    bool isCharging;
    bool isExPower;
} Power_Info_t;

/* Storage */
typedef struct
{
    bool isDetect;
    float sizeMB;
    const char* type;
} Storage_Info_t;

/* Led */
typedef struct
{
    int32_t key;
    int32_t event;
} Key_Info_t;

/* WiFi */
typedef struct
{
    bool isConnected;
    String SSID;
    String IP;
    int8_t RSSI;
} WiFi_Info_t;

/* FFS */
typedef struct
{
    String Name;
    String Value;
} Config_Info_t;

}


#endif
