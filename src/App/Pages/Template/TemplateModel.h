#ifndef __TEMPLATE_MODEL_H
#define __TEMPLATE_MODEL_H

#include "lvgl.h"
#include "App/DataProc/DataProc.h"

namespace Page
{

class TemplateModel
{
public:
    void Init();
    void DeInit();
    uint32_t TickSave;
    uint32_t GetData();
};

}

#endif
