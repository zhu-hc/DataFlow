#ifndef __SERIAL_PRESENTER_H
#define __SERIAL_PRESENTER_H

#include "SerialView.h"
#include "SerialModel.h"
#include "App/Utils/ButtonEvent/ButtonEvent.h"

#define BANDRATE_C1 2400
#define BANDRATE_C2 1500000

namespace Page
{

class Serial : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;
    typedef struct
    {
        uint32_t baud;
        uint16_t led;
    } BaudRate_t;
public:
    Serial();
    virtual ~Serial();

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
    void SetBaud(int32_t index);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);
    static int onAccountEvent(Account* account, Account::EventParam_t* param);

private:
    SerialView View;
    SerialModel Model;
    lv_timer_t* timer;
    Account* account;
    int32_t baud_index;
};

}

#endif
