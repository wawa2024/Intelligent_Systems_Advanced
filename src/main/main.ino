/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#include "Debug.h"
#include "WindDirection.h"
#include "WindSpeed.h"
#include "LCD.h"
#include "Keypad.h"
#include "COM.h"

void setup()
{
    COM::Init();
    LCD::Init();
    Keypad::Init();
    WindSpeed::Init();
    WindDirection::Init();
}

void loop()
{
    Keypad::Exec();
}
