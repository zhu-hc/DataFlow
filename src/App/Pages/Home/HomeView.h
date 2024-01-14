#ifndef __HOME_VIEW_H
#define __HOME_VIEW_H

#include "../Page.h"

namespace Page
{

class HomeView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    struct
    {
        lv_obj_t *menu;
        lv_group_t *group;
    } ui;

private:

};

}

#endif // !__VIEW_H
