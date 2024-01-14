#include "Home.h"

using namespace Page;

static int32_t app = 0;

Home::Home()
{
}

Home::~Home()
{

}

void Home::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Home::onViewLoad()
{
	Model.Init();
	View.Create(root);

	AttachEvent(root);
	AttachEvent(View.ui.menu);

	// Init
	lv_img_set_src(View.ui.menu, Resource.GetImage(Model.GetAppInfo(app)->icon));
}

void Home::onViewDidLoad()
{

}

void Home::onViewWillAppear()
{
	Param_t param;
	param.color = lv_color_white();
	param.time = 1000;

	PAGE_STASH_POP(param);

	lv_obj_set_style_bg_color(root, param.color, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(root, LV_OPA_COVER, LV_PART_MAIN);
	timer = lv_timer_create(onTimerUpdate, param.time, this);

	Model.SetStatusBarAppear(true);
	Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_BLACK);
}

void Home::onViewDidAppear()
{

}

void Home::onViewWillDisappear()
{

}

void Home::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void Home::onViewUnload()
{
	View.Delete();
	Model.DeInit();
}

void Home::onViewDidUnload()
{

}

void Home::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Home::Update()
{

}

void Home::onTimerUpdate(lv_timer_t* timer)
{
	Home* instance = (Home*)timer->user_data;

	instance->Update();
}

void Home::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	Home* instance = (Home*)lv_obj_get_user_data(obj);

	if (code == LV_EVENT_KEY)
	{
		uint32_t key = lv_event_get_key(event);
		int32_t cnt = instance->Model.GetAppCount();
		switch (key)
		{
		case LV_KEY_LEFT:
			if (--app < 0) app += cnt;
			break;
		case LV_KEY_RIGHT:
			if (++app >= cnt) app -= cnt;
			break;
		case LV_KEY_ENTER:
			instance->Model.SetStatusBarAppear(false);
			instance->Manager->Replace(instance->Model.GetAppInfo(app)->page);
			break;
		}
		lv_img_set_src(instance->View.ui.menu, Resource.GetImage(instance->Model.GetAppInfo(app)->icon));
	}
}
