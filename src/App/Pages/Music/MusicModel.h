#ifndef __MUSIC_MODEL_H
#define __MUSIC_MODEL_H

#include "lvgl.h"
#include "App/DataProc/DataProc.h"

namespace Page
{

class MusicModel
{
public:
    void Init();
    void DeInit();
    void SetEventCallback(void (*event)(int, int, void*), void *data);
    void (*KeyEvent)(int key, int event, void *data);
    void *userData;

private:
    Account* account;
};

}

#endif
