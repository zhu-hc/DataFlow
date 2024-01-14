#include "HAL/HAL.h"
#include "App/Utils/ButtonEvent/ButtonEvent.h"

static HAL::CommitFunc_t CommitFunc;
static void* UserData;

static ButtonEvent LeftPush(5000);
static ButtonEvent RightPush(5000);

static void Left_PushHandler(ButtonEvent* btn, int event)
{
  HAL::Key_Info_t key;
  key.event = event;
  key.key = Key_Value_t::Left;
  if (CommitFunc) CommitFunc(&key, UserData);
}

static void Right_PushHandler(ButtonEvent* btn, int event)
{
  HAL::Key_Info_t key;
  key.event = event;
  key.key = Key_Value_t::Right;
  if (CommitFunc) CommitFunc(&key, UserData);
}

void HAL::Key_Init()
{
  pinMode(CONFIG_KEY_LEFT_PIN, INPUT_PULLUP);
  pinMode(CONFIG_KEY_RIGHT_PIN, INPUT_PULLUP);

  LeftPush.EventAttach(Left_PushHandler);
  RightPush.EventAttach(Right_PushHandler);
}

void HAL::Key_Update()
{
  LeftPush.EventMonitor(digitalRead(CONFIG_KEY_LEFT_PIN) == LOW);
  RightPush.EventMonitor(digitalRead(CONFIG_KEY_RIGHT_PIN) == LOW);
}

void HAL::Key_SetCommitCallback(CommitFunc_t func, void* userData)
{
  CommitFunc = func;
  UserData = userData;
}