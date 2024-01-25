#ifndef __SERIAL_VIEW_H
#define __SERIAL_VIEW_H

#include "../Page.h"

namespace Page
{

class SerialView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    struct
    {
        lv_obj_t* labelTitle;
        lv_obj_t* labelTick;
    } ui;

private:

};

}

#endif // !__VIEW_H
