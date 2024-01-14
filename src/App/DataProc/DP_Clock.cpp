#include "DataProc.h"
#include "HAL/HAL.h"

static void onTimer(Account* account)
{
  HAL::WiFi_Info_t wifi;
  if(account->Pull("WiFi", &wifi, sizeof(wifi)) != Account::RES_OK) return;
  if (!wifi.isConnected) return;

  HAL::Clock_NTP();
  account->SetTimerEnable(false);
}

static int onEvent(Account* account, Account::EventParam_t* param)
{
  if (param->event == Account::EVENT_TIMER)
  {
    onTimer(account);
    return Account::RES_OK;
  }

  if (param->event != Account::EVENT_SUB_PULL)
  {
    return Account::RES_UNSUPPORTED_REQUEST;
  }

  if (param->size != sizeof(HAL::Clock_Info_t))
  {
    return Account::RES_SIZE_MISMATCH;
  }

  HAL::Clock_Info_t* info = (HAL::Clock_Info_t*)param->data_p;
  HAL::Clock_GetInfo(info);

  return Account::RES_OK;
}

DATA_PROC_INIT_DEF(Clock)
{
  account->Subscribe("WiFi");
  account->SetEventCallback(onEvent);
  account->SetTimerPeriod(1000);
}
