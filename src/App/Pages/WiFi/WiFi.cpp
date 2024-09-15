#include "WiFi.h"

using namespace Page;

WiFi::WiFi()
{
}

WiFi::~WiFi()
{

}

void WiFi::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void WiFi::onViewLoad()
{
	Model.Init();

	View.Create(root);
	AttachEvent(root);

	account = new Account("WiFiPage", DataProc::Center(), 0, this);
	account->Subscribe("Key");
	account->Subscribe("WiFi");
	account->SetEventCallback(onAccountEvent);
}

void WiFi::onViewDidLoad()
{

}

void WiFi::onViewWillAppear()
{
	Param_t param;
	param.color = lv_color_white();
	param.time = 1000;

	PAGE_STASH_POP(param);

	lv_obj_set_style_bg_color(root, param.color, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(root, LV_OPA_COVER, LV_PART_MAIN);
	timer = lv_timer_create(onTimerUpdate, param.time, this);
}

void WiFi::onViewDidAppear()
{

}

void WiFi::onViewWillDisappear()
{

}

void WiFi::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void WiFi::onViewUnload()
{
	View.Delete();
	Model.DeInit();

	if (account)
	{
		delete account;
		account = nullptr;
	}
}

void WiFi::onViewDidUnload()
{

}

void WiFi::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void WiFi::Update()
{
	HAL::WiFi_Info_t info;
	if(account->Pull("WiFi", &info, sizeof(info)) == Account::RES_OK)
	{
		String str = 			
			"Stat:" + String(info.isConnected) + "\r\n"
			"IP:  " + info.IP + "\r\n"
			"RSSI:" + info.RSSI + "\r\n"
			"SSID:" + info.SSID;

		lv_label_set_text(View.ui.labelInfo, str.c_str());
	}
	else
	{
		lv_label_set_text(View.ui.labelInfo, "未查询到WiFi信息");
	}
}

void WiFi::onTimerUpdate(lv_timer_t* timer)
{
	WiFi* instance = (WiFi*)timer->user_data;

	instance->Update();
}

void WiFi::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	WiFi* instance = (WiFi*)lv_obj_get_user_data(obj);

	if (obj == instance->View.ui.labelInfo && code == LV_EVENT_KEY)
	{

	}
}

int WiFi::onAccountEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event == Account::EVENT_PUB_PUBLISH)
    {
        if (param->size == sizeof(HAL::Key_Info_t))
        {
            HAL::Key_Info_t *key = (HAL::Key_Info_t*)param->data_p;
            // LV_LOG_WARN("Key %d = %d\r\n", key->key, key->event);
            WiFi* instance = (WiFi*)account->UserData;
						if (key->key == Key_Value_t::Right && key->event == ButtonEvent::EVENT_LONG_PRESSED)
						{
							instance->Manager->Replace("Pages/Home");
						}
        }
        
        return Account::RES_OK;
    }

    return Account::RES_OK;
}