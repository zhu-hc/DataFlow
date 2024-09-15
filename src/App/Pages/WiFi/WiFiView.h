#ifndef __WIFI_VIEW_H
#define __WIFI_VIEW_H

#include "../Page.h"

namespace Page
{

class WiFiView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    struct
    {
        lv_obj_t* labelInfo;
    } ui;

private:

};

}

#endif // !__VIEW_H
