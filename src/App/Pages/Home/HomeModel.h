#ifndef __HOME_MODEL_H
#define __HOME_MODEL_H

#include "lvgl.h"
#include "App/DataProc/DataProc.h"

namespace Page
{

typedef struct
{
    const char *name;
    const char *icon;
    const char *page;
} AppInfo;

class HomeModel
{
public:
    void Init();
    void DeInit();
    AppInfo* GetAppInfo(int32_t cnt);
    int32_t GetAppCount();
    void SetStatusBarAppear(bool en);
    void SetStatusBarStyle(DataProc::StatusBar_Style_t style);
    void SetStatusBarLable(const char *str, bool show);
private:
    Account* account;
};

}

#endif
