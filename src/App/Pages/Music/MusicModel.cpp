#include "MusicModel.h"

using namespace Page;

static int onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event == Account::EVENT_PUB_PUBLISH)
    {
        if (param->size == sizeof(HAL::Key_Info_t))
        {
            HAL::Key_Info_t *key = (HAL::Key_Info_t*)param->data_p;
            // LV_LOG_WARN("Key %d = %d\r\n", key->key, key->event);
            MusicModel* instance = (MusicModel*)account->UserData;
            if (instance->KeyEvent) instance->KeyEvent(key->key, key->event, instance->userData);
        }
        
        return Account::RES_OK;
    }

    return Account::RES_OK;
}

void MusicModel::Init()
{
    account = new Account("MusicModel", DataProc::Center(), 0, this);
    account->Subscribe("StatusBar");
    account->Subscribe("Key");
    account->SetEventCallback(onEvent);
}

void MusicModel::DeInit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

void MusicModel::SetEventCallback(void (*event)(int, int, void*), void *data)
{
    this->userData = data;
    this->KeyEvent = event;
}