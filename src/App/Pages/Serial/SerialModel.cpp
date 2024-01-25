#include "SerialModel.h"

using namespace Page;

void SerialModel::Init()
{

}

void SerialModel::DeInit()
{

}

uint32_t SerialModel::GetData()
{
    return lv_tick_get();
}
