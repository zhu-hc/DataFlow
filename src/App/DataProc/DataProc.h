#ifndef __DATA_PROC_H
#define __DATA_PROC_H

#include "App/Utils/DataCenter/DataCenter.h"
#include "HAL/HAL_Def.h"
#include "DataProc_Def.h"

#define DATA_PROC_INIT_DEF(name)   void _DP_##name##_Init(Account* account)
#define DATA_PROC_INIT_STRUCT(sct) memset(&sct, 0, sizeof(sct))

void DataProc_Init();

namespace DataProc
{

DataCenter* Center();

}

#endif