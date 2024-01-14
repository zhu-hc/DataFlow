#include "Music.h"

using namespace Page;

Music::Music()
{
}

Music::~Music()
{

}

void Music::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Music::onViewLoad()
{
	Model.Init();

	View.Create(root);
	lv_label_set_text(View.ui.labelTitle, Name);

	AttachEvent(root);

	Model.SetEventCallback(onKeyEvent, this);
}

void Music::onViewDidLoad()
{

}

void Music::onViewWillAppear()
{
	Param_t param;
	param.color = lv_color_white();
	param.time = 1000;

	PAGE_STASH_POP(param);

	lv_obj_set_style_bg_color(root, param.color, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(root, LV_OPA_COVER, LV_PART_MAIN);
	timer = lv_timer_create(onTimerUpdate, param.time, this);
}

void Music::onViewDidAppear()
{

}

void Music::onViewWillDisappear()
{

}

void Music::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void Music::onViewUnload()
{
    View.Delete();
    Model.DeInit();
}

void Music::onViewDidUnload()
{

}

void Music::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Music::Update()
{
	lv_label_set_text_fmt(View.ui.labelTick, "tick = %d save = %d", 123, 456);
}

void Music::onTimerUpdate(lv_timer_t* timer)
{
	Music* instance = (Music*)timer->user_data;

	instance->Update();
}


void Music::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	Music* instance = (Music*)lv_obj_get_user_data(obj);

	if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LEAVE)
	{
		// instance->Manager->Pop();
	}
}

void Music::onKeyEvent(int key, int event, void *data)
{
	if (key == Key_Value_t::Right && event == ButtonEvent::EVENT_LONG_PRESSED)
	{
		Music* instance = (Music*)data;
		instance->Manager->Replace("Pages/Home");
	}
}
