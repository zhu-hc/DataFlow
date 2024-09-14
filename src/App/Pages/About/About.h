#ifndef __ABOUT_PRESENTER_H
#define __ABOUT_PRESENTER_H

#include "AboutView.h"
#include "AboutModel.h"
#include "App/Utils/ButtonEvent/ButtonEvent.h"

namespace Page
{

class About : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    About();
    virtual ~About();

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
    static int onAccountEvent(Account* account, Account::EventParam_t* param);

private:
    AboutView View;
    AboutModel Model;
    lv_timer_t* timer;
    Account* account;
};

}

#endif
