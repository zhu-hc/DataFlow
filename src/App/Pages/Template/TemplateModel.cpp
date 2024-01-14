#include "TemplateModel.h"

using namespace Page;

void TemplateModel::Init()
{

}

void TemplateModel::DeInit()
{

}

uint32_t TemplateModel::GetData()
{
    return lv_tick_get();
}
