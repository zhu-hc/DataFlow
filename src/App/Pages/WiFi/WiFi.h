#ifndef __WIFI_PRESENTER_H
#define __WIFI_PRESENTER_H

#include "WiFiView.h"
#include "WiFiModel.h"
#include "App/Utils/ButtonEvent/ButtonEvent.h"

namespace Page
{

class WiFi : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    WiFi();
    virtual ~WiFi();

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
    WiFiView View;
    WiFiModel Model;
    lv_timer_t* timer;
    Account* account;
};

}

#endif
