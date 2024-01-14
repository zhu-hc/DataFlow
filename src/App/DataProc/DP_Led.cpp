#include "DataProc.h"
#include "HAL/HAL.h"


static int onEvent(Account* account, Account::EventParam_t* param)
{
  if (param->event != Account::EVENT_NOTIFY)
  {
    return Account::RES_UNSUPPORTED_REQUEST;
  }

  if (param->size != sizeof(HAL::Led_Info_t))
  {
    return Account::RES_SIZE_MISMATCH;
  }

  HAL::Led_Info_t* info = (HAL::Led_Info_t*)param->data_p;
  HAL::Led_SetValue(info);

  return Account::RES_OK;
}

DATA_PROC_INIT_DEF(Led)
{
  account->SetEventCallback(onEvent);
}
