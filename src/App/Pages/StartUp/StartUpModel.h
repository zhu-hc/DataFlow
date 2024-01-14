#ifndef __STARTUP_MODEL_H
#define __STARTUP_MODEL_H

#include "App/DataProc/DataProc.h"
#include "HAL/HAL.h"

namespace Page
{

class StartupModel
{
public:
    void Init();
    void DeInit();
    void SetStatusBarAppear(bool en);
    void SetStatusBarStyle(DataProc::StatusBar_Style_t style);
    void SetStatusBarLable(const char *str, bool show);
private:
    Account* account;
};

}

#endif
