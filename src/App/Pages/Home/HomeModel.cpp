#include "HomeModel.h"

using namespace Page;

static AppInfo Apps[] = {
  {
    .name = "音乐",
    .icon = "icon_music",
    .page = "Pages/Music"
  },
  {
    .name = "关于",
    .icon = "icon_about",
    .page = "About"
  },
  {
    .name = "设置",
    .icon = "icon_setting",
    .page = "Setting"
  },
  {
    .name = "WiFi",
    .icon = "icon_wifi",
    .page = "Pages/WiFi"
  },
  {
    .name = "串口",
    .icon = "icon_serial",
    .page = "Pages/Serial"
  },
  {
    .name = "示波器",
    .icon = "icon_scope",
    .page = "Pages/Scope"
  },
  {
    .name = "FTP",
    .icon = "icon_ftp",
    .page = "Pages/FTP"
  }
};

void HomeModel::Init()
{
    account = new Account("HomeModel", DataProc::Center(), 0, this);
    account->Subscribe("StatusBar");
}

void HomeModel::DeInit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

void HomeModel::SetStatusBarAppear(bool en)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);
    info.cmd = DataProc::STATUS_BAR_CMD_APPEAR;
    info.param.appear = en;
    account->Notify("StatusBar", &info, sizeof(info));
}

void HomeModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_STYLE;
    info.param.style = style;

    account->Notify("StatusBar", &info, sizeof(info));
}

void HomeModel::SetStatusBarLable(const char *str, bool show)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_LABEL_REC;
    info.param.labelRec.str = str;
    info.param.labelRec.show = show;

    account->Notify("StatusBar", &info, sizeof(info));
}

int32_t HomeModel::GetAppCount()
{
  return sizeof(Apps) / sizeof(Apps[0]);
}

AppInfo* HomeModel::GetAppInfo(int32_t cnt)
{
  if (cnt < 0 || cnt >= GetAppCount()) return NULL;
  return &Apps[cnt];
}
