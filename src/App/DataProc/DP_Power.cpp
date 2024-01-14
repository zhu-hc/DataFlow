#include "DataProc.h"
#include "HAL/HAL.h"
#include "App/Utils/Filters/Filters.h"

static int onEvent(Account* account, Account::EventParam_t* param)
{
    static Filter::Hysteresis<int16_t>      battUsageHysFilter(2);
    static Filter::MedianQueue<int16_t, 10> battUsageMqFilter;

    if (param->event != Account::EVENT_SUB_PULL)
    {
        return Account::RES_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::Power_Info_t))
    {
        return Account::RES_SIZE_MISMATCH;
    }

    HAL::Power_Info_t powerInfo;
    HAL::Power_GetInfo(&powerInfo);

    int16_t usage = powerInfo.usage;
    usage = battUsageHysFilter.GetNext(usage);
    usage = battUsageMqFilter.GetNext(usage);
    powerInfo.usage = (uint8_t)usage;

    memcpy(param->data_p, &powerInfo, param->size);

    return Account::RES_OK;
}

DATA_PROC_INIT_DEF(Power)
{
    account->SetEventCallback(onEvent);
}
