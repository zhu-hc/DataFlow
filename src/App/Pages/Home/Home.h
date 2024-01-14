#ifndef __HOME_PRESENTER_H
#define __HOME_PRESENTER_H

#include "HomeView.h"
#include "HomeModel.h"

namespace Page
{

class Home : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Home();
    virtual ~Home();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewUnload();
    virtual void onViewDidUnload();

private:
    void Update();
    void AttachEvent(lv_obj_t* obj);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    HomeView View;
    HomeModel Model;
    lv_timer_t* timer;
};

}

#endif
