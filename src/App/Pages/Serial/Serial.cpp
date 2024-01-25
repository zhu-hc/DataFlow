#include "Serial.h"

using namespace Page;

Serial::Serial()
{

}

Serial::~Serial()
{

}

void Serial::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Serial::onViewLoad()
{
	Model.Init();

	View.Create(root);
	lv_label_set_text(View.ui.labelTitle, Name);

	AttachEvent(root);

	Model.TickSave = Model.GetData();

	account = new Account("Serial", DataProc::Center(), 0, this);
	account->Subscribe("Key");
	account->SetEventCallback(onAccountEvent);
}

void Serial::onViewDidLoad()
{

}

void Serial::onViewWillAppear()
{
	Param_t param;
	param.color = lv_color_white();
	param.time = 1000;

	PAGE_STASH_POP(param);

	lv_obj_set_style_bg_color(root, param.color, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(root, LV_OPA_COVER, LV_PART_MAIN);
	timer = lv_timer_create(onTimerUpdate, param.time, this);
}

void Serial::onViewDidAppear()
{

}

void Serial::onViewWillDisappear()
{

}

void Serial::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void Serial::onViewUnload()
{
	View.Delete();
	Model.DeInit();

	if (account)
	{
		delete account;
		account = nullptr;
	}
}

void Serial::onViewDidUnload()
{

}

void Serial::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Serial::Update()
{
	lv_label_set_text_fmt(View.ui.labelTick, "tick = %d save = %d", Model.GetData(), Model.TickSave);
}

void Serial::onTimerUpdate(lv_timer_t* timer)
{
	Serial* instance = (Serial*)timer->user_data;

	instance->Update();
}

void Serial::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	Serial* instance = (Serial*)lv_obj_get_user_data(obj);

	if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LEAVE)
	{

	}
}

int Serial::onAccountEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event == Account::EVENT_PUB_PUBLISH)
    {
        if (param->size == sizeof(HAL::Key_Info_t))
        {
            HAL::Key_Info_t *key = (HAL::Key_Info_t*)param->data_p;
            // LV_LOG_WARN("Key %d = %d\r\n", key->key, key->event);
            Serial* instance = (Serial*)account->UserData;
						if (key->key == Key_Value_t::Right && key->event == ButtonEvent::EVENT_LONG_PRESSED)
						{
							instance->Manager->Replace("Pages/Home");
						}
        }
        
        return Account::RES_OK;
    }

    return Account::RES_OK;
}