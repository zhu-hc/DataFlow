#include "StartupModel.h"

using namespace Page;

void StartupModel::Init()
{
    account = new Account("StartupModel", DataProc::Center(), 0, this);
    account->Subscribe("StatusBar");
}

void StartupModel::DeInit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

void StartupModel::SetStatusBarAppear(bool en)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);
    info.cmd = DataProc::STATUS_BAR_CMD_APPEAR;
    info.param.appear = en;
    account->Notify("StatusBar", &info, sizeof(info));
}

void StartupModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_STYLE;
    info.param.style = style;

    account->Notify("StatusBar", &info, sizeof(info));
}

void StartupModel::SetStatusBarLable(const char *str, bool show)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_LABEL_REC;
    info.param.labelRec.str = str;
    info.param.labelRec.show = show;

    account->Notify("StatusBar", &info, sizeof(info));
}
