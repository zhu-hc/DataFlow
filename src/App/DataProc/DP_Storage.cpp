#include "DataProc.h"
#include "HAL/HAL.h"


static int onEvent(Account* account, Account::EventParam_t* param)
{
  if (param->event != Account::EVENT_SUB_PULL)
  {
    return Account::RES_UNSUPPORTED_REQUEST;
  }

  if (param->size != sizeof(HAL::Storage_Info_t))
  {
    return Account::RES_SIZE_MISMATCH;
  }

  HAL::Storage_Info_t* info = (HAL::Storage_Info_t*)param->data_p;
  HAL::SD_GetInfo(info);

  return Account::RES_OK;
}


DATA_PROC_INIT_DEF(Storage)
{
  account->SetEventCallback(onEvent);
}
