#include "About.h"

using namespace Page;

About::About()
{
}

About::~About()
{

}

void About::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void About::onViewLoad()
{
	Model.Init();

	View.Create(root);
	AttachEvent(root);

	account = new Account("About", DataProc::Center(), 0, this);
	account->Subscribe("Key");
	account->Subscribe("System");
	account->SetEventCallback(onAccountEvent);

	HAL::System_Info_t info;
	if(account->Pull("System", &info, sizeof(info)) == Account::RES_OK)
	{
		String str = 			
			"设备名称:" + info.Name + "\r\n"
			"软件版本:" + info.Software + "\r\n"
			"硬件版本:" + info.Hardware + "\r\n"
			"产品作者:" + info.Author;

		lv_label_set_text(View.ui.labelInfo, str.c_str());
	}
	else
	{
		lv_label_set_text(View.ui.labelInfo, "未查询到版本信息");
	}
}

void About::onViewDidLoad()
{

}

void About::onViewWillAppear()
{
	Param_t param;
	param.color = lv_color_white();
	param.time = 1000;

	PAGE_STASH_POP(param);

	lv_obj_set_style_bg_color(root, param.color, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(root, LV_OPA_COVER, LV_PART_MAIN);
	timer = lv_timer_create(onTimerUpdate, param.time, this);
}

void About::onViewDidAppear()
{

}

void About::onViewWillDisappear()
{

}

void About::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void About::onViewUnload()
{
	View.Delete();
	Model.DeInit();

	if (account)
	{
		delete account;
		account = nullptr;
	}
}

void About::onViewDidUnload()
{

}

void About::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void About::Update()
{

}

void About::onTimerUpdate(lv_timer_t* timer)
{
	About* instance = (About*)timer->user_data;

	instance->Update();
}

void About::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	About* instance = (About*)lv_obj_get_user_data(obj);

	if (obj == instance->View.ui.labelInfo && code == LV_EVENT_KEY)
	{

	}
}

int About::onAccountEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event == Account::EVENT_PUB_PUBLISH)
    {
        if (param->size == sizeof(HAL::Key_Info_t))
        {
            HAL::Key_Info_t *key = (HAL::Key_Info_t*)param->data_p;
            // LV_LOG_WARN("Key %d = %d\r\n", key->key, key->event);
            About* instance = (About*)account->UserData;
						if (key->key == Key_Value_t::Right && key->event == ButtonEvent::EVENT_LONG_PRESSED)
						{
							instance->Manager->Replace("Pages/Home");
						}
        }
        
        return Account::RES_OK;
    }

    return Account::RES_OK;
}