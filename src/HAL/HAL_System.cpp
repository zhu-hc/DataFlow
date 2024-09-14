#include "HAL/HAL.h"


void HAL::System_GetInfo(System_Info_t* const info)
{
  info->Name = VERSION_FIRMWARE_NAME;
  info->Software = VERSION_HARDWARE;
  info->Hardware = VERSION_HARDWARE;
  info->Author = VERSION_AUTHOR_NAME;
}