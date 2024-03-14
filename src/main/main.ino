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
    Keypad::Init();
    WindSpeed::Init();
    WindDirection::Init();
}

void loop()
{
    LCD::Draw::Alphabet();
    //Keypad::Exec();
    //delay(250);
}
