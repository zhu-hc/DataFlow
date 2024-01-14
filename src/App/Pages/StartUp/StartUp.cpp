#include "StartUp.h"

using namespace Page;

Startup::Startup()
{
}

Startup::~Startup()
{

}

void Startup::onCustomAttrConfig()
{
    SetCustomCacheEnable(false);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void Startup::onViewLoad()
{
    Model.Init();
    View.Create(root);
    lv_timer_t* timer = lv_timer_create(onTimer, 2000, this);
    lv_timer_set_repeat_count(timer, 1);
}

void Startup::onViewDidLoad()
{

}

void Startup::onViewWillAppear()
{
    lv_anim_timeline_start(View.ui.anim_timeline);
}

void Startup::onViewDidAppear()
{
    lv_obj_fade_out(root, 500, 1500);
}

void Startup::onViewWillDisappear()
{

}

void Startup::onViewDidDisappear()
{
    // Model.SetStatusBarAppear(true);
    // Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_BLACK);
    // Model.SetStatusBarLable("Test", true);
}

void Startup::onViewUnload()
{
    View.Delete();
    Model.DeInit();
}

void Startup::onViewDidUnload()
{

}

void Startup::onTimer(lv_timer_t* timer)
{
    Startup* instance = (Startup*)timer->user_data;
    instance->Manager->Replace("Pages/Home");
}
