#ifndef __MUSIC_PRESENTER_H
#define __MUSIC_PRESENTER_H

#include "MusicView.h"
#include "MusicModel.h"
#include "App/Utils/ButtonEvent/ButtonEvent.h"

namespace Page
{

class Music : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Music();
    virtual ~Music();

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
    static void onKeyEvent(int key, int event, void *data);

private:
    MusicView View;
    MusicModel Model;
    lv_timer_t* timer;
    Account* account;
};

}

#endif
