/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#include "Utils.h"
#include "Debug.h"
#include "WindDirection.h"
#include "WindSpeed.h"
#include "LCD.h"
#include "Keypad.h"
#include "COM.h"
#include "NET.h"

void setup()
{
    COM::Init();
    LCD::Init();
    Keypad::Init();
    WindSpeed::Init();
    WindDirection::Init();
    NET::Init();
}

void loop()
{
    Keypad::Exec();
}
