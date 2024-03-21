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
#include "Protocol.h"

void setup()
{
    COM::Init();
    LCD::Init();
    Keypad::Init();
    WindSpeed::Init();
    WindDirection::Init();
    NET::Init();
    MQTT::Init();
}

void loop()
{
    Keypad::Exec();
}
