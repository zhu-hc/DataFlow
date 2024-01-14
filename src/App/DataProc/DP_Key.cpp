#include "DataProc.h"
#include "HAL/HAL.h"

DATA_PROC_INIT_DEF(Key)
{
  HAL::Key_SetCommitCallback([](void* info, void* userData){
    Account* account = (Account*)userData;
    bool result = account->Commit(info, sizeof(HAL::Key_Info_t));
    account->Publish();
    return result;
  }, account);
}
