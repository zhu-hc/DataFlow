#include "DataProc.h"
#include "HAL/HAL.h"


static int onEvent(Account* account, Account::EventParam_t* param)
{
  if (param->size != sizeof(HAL::Config_Info_t))
  {
    return Account::RES_SIZE_MISMATCH;
  }

  HAL::Config_Info_t* info = (HAL::Config_Info_t*)param->data_p;

  // 获取配置
  if (param->event == Account::EVENT_SUB_PULL)
  {
    if (HAL::FFS_ReadConfig(param->tran->ID, info))
      return Account::RES_OK;
    else
      return Account::RES_UNKNOW;
  }

  // 存储配置
  if (param->event == Account::EVENT_NOTIFY)
  {
    if (HAL::FFS_WriteConfig(param->tran->ID, info))
      return Account::RES_OK;
    else
      return Account::RES_UNKNOW;
  }

  return Account::RES_UNSUPPORTED_REQUEST;
}


DATA_PROC_INIT_DEF(Config)
{
  account->SetEventCallback(onEvent);
}
