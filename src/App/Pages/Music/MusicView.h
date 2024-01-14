#ifndef __MUSIC_VIEW_H
#define __MUSIC_VIEW_H

#include "../Page.h"

namespace Page
{

class MusicView
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
