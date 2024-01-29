#include "HAL/HAL.h"
#include <SD_MMC.h>

static bool SD_IsReady = false;
static uint32_t SD_Size = 0;
static HAL::SD_CallbackFunction_t SD_EventCallback = nullptr;

bool HAL::SD_Init()
{
    bool retval = true;
    pinMode(CONFIG_SD_CD_PIN, INPUT_PULLUP);
    SD_MMC.setPins(CONFIG_SD_SCK_PIN, CONFIG_SD_CMD_PIN, CONFIG_SD_DATA0_PIN);

    if (digitalRead(CONFIG_SD_CD_PIN))
    {
        Serial.println("SD: CARD was not inserted");
        retval = false;
    }

    retval = SD_MMC.begin("/sd", true, false, SDMMC_FREQ_DEFAULT);
    if (!retval) 
    {
        Serial.println("Card Mount Failed");
        retval = false;
    }
    else
    {
        uint8_t cardType = SD_MMC.cardType();

        if (cardType == CARD_NONE)
        {
            Serial.println("No SD card attached");
            return false;
        }

        Serial.print("SD Card Type: ");
        if (cardType == CARD_MMC)
        {
            Serial.println("MMC");
        } else if (cardType == CARD_SD)
        {
            Serial.println("SDSC");
        } else if (cardType == CARD_SDHC)
        {
            Serial.println("SDHC");
        } else
        {
            Serial.println("UNKNOWN");
        }

        SD_Size = SD_MMC.cardSize() / (1024 * 1024);
        Serial.printf("SD Card Size: %d MB\n", SD_Size);
    }

    SD_IsReady = retval;
    return retval;
}

bool HAL::SD_GetReady()
{
    return SD_IsReady;
}

uint32_t HAL::SD_GetSizeMB()
{
    return SD_Size;
}

const char* HAL::SD_GetTypeName()
{
    const char* type = "Unknown";

    switch (SD_MMC.cardType())
    {
    case CARD_MMC:
        type = "MMC";
        break;

    case CARD_SD:
        type = "SDSC";
        break;

    case CARD_SDHC:
        type = "SDHC";
        break;

    default:
        break;
    }

    return type;
}

static void SD_Check(bool isInsert)
{
    if(isInsert)
    {
        delay(1000);
        bool ret = HAL::SD_Init();

        if(ret && SD_EventCallback)
        {
            SD_EventCallback(true);
        }
    }
    else
    {
        SD_IsReady = false;
        SD_MMC.end();
        if(SD_EventCallback)
        {
            SD_EventCallback(false);
            SD_Size = 0;
        }
    }
}

void HAL::SD_GetInfo(Storage_Info_t* const info)
{
    info->isDetect = SD_GetReady();
    info->sizeMB = SD_GetSizeMB();
    info->type = SD_GetTypeName();
}

void HAL::SD_SetEventCallback(SD_CallbackFunction_t callback)
{
    SD_EventCallback = callback;
}

void HAL::SD_Update()
{
    bool isInsert = (digitalRead(CONFIG_SD_CD_PIN) == LOW);

    CM_VALUE_MONITOR(isInsert, SD_Check(isInsert));
}

