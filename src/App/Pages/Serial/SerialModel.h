#ifndef __SERIAL_MODEL_H
#define __SERIAL_MODEL_H

#include "lvgl.h"
#include "App/DataProc/DataProc.h"

namespace Page
{

class SerialModel
{
public:
    void Init();
    void DeInit();
    uint32_t TickSave;
    uint32_t GetData();
};

}

#endif
