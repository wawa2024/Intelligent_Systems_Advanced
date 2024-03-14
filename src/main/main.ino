/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#include "WindDirection.h"
#include "WindSpeed.h"
#include "Keypad.h"
#include "LCD.h"
#include "COM.h"

void setup()
{
    COM::Init();
    LCD::Init();
    WindSpeed::Init();
    WindDirection::Init();
}

void loop()
{
   COM::Print::Stats(); 
   LCD::Draw::Stats();
   delay(250);
}
