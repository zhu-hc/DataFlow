#include "Serial.h"

using namespace Page;

static Serial::BaudRate_t bauds[] = {
	{ .baud = BANDRATE_C1, .led = 0x0001 },
	{ .baud = 4800,        .led = 0x0002 },
	{ .baud = 9600,        .led = 0x0004 },
	{ .baud = 19200,       .led = 0x0008 },
	{ .baud = 38400,       .led = 0x0010 },
	{ .baud = 57600,       .led = 0x0020 },
	{ .baud = 115200,      .led = 0x0040 },
	{ .baud = 230400,      .led = 0x0080 },
	{ .baud = 460800,      .led = 0x0100 },
	{ .baud = 921600,      .led = 0x0200 },
	{ .baud = BANDRATE_C2, .led = 0x0400 }
};

Serial::Serial()
{

}

Serial::~Serial()
{

}

void Serial::SetBaud(int32_t index)
{
	baud_index = index;

	HAL::Led_Info_t info;
	info.led = Led_Value_t::Rear;
	info.data = index >= 0 ? bauds[baud_index].led : 0x0;
	account->Notify("Led", &info, sizeof(info));

	lv_label_set_text_fmt(View.ui.labelBaud, "%d", bauds[baud_index].baud);
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
	lv_label_set_text(View.ui.labelBaud, Name);

	AttachEvent(root);
	AttachEvent(View.ui.labelBaud);

	account = new Account("Serial", DataProc::Center(), 0, this);
	account->Subscribe("Key");
	account->Subscribe("Led");
	account->Subscribe("Config");
	account->SetEventCallback(onAccountEvent);

	// 配置
	HAL::Config_Info_t info;
	info.Name = "C1";
	if(account->Pull("Config", &info, sizeof(info)) == Account::RES_OK)
	{
		bauds[0].baud = atoi(info.Value.c_str());
	}
	else
	{
		info.Value = String(bauds[0].baud);
	  account->Notify("Config", &info, sizeof(info));
	}
	info.Name = "C2";
	if(account->Pull("Config", &info, sizeof(info)) == Account::RES_OK)
	{
		bauds[10].baud = atoi(info.Value.c_str());
	}
	else
	{
		info.Value = String(bauds[10].baud);
	  account->Notify("Config", &info, sizeof(info));
	}

	SetBaud(6);
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
	SetBaud(-1);

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

	if (obj == instance->View.ui.labelBaud && code == LV_EVENT_KEY)
	{
		uint32_t key = lv_event_get_key(event);
		int32_t index = instance->baud_index;
		switch (key)
		{
		case LV_KEY_LEFT:
			instance->SetBaud(instance->baud_index <= 0 ? (sizeof(bauds) / sizeof(Serial::BaudRate_t) - 1) : (instance->baud_index - 1));
			break;
		case LV_KEY_RIGHT:
			instance->SetBaud(instance->baud_index >= (sizeof(bauds) / sizeof(Serial::BaudRate_t) - 1) ? 0 : (instance->baud_index + 1));
			break;
		case LV_KEY_ENTER:
			break;
		}
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