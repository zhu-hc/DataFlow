#include "DataProc.h"
#include "HAL/HAL.h"


static int onEvent(Account* account, Account::EventParam_t* param)
{
  if (param->event != Account::EVENT_SUB_PULL)
  {
    return Account::RES_UNSUPPORTED_REQUEST;
  }

  if (param->size != sizeof(HAL::WiFi_Info_t))
  {
    return Account::RES_SIZE_MISMATCH;
  }

  HAL::WiFi_Info_t* info = (HAL::WiFi_Info_t*)param->data_p;
  HAL::WiFi_GetInfo(info);

  return Account::RES_OK;
}


DATA_PROC_INIT_DEF(WiFi)
{
  account->SetEventCallback(onEvent);
}
