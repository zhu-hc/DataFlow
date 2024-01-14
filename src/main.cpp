#include <Arduino.h>
#include "HAL/HAL.h"
#include "Port/Display.h"
#include "App/App.h"

void setup() 
{
    HAL::Init();
    Port::Init();
    App::Init();

    HAL::Power_SetEventCallback(App::UnInit);
}

void loop() 
{
    HAL::Update();
    delay(20);
}
