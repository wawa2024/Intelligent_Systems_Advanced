/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#define NoDebug

#include "Utils.h"
#include "WindDirection.h"
#include "WindSpeed.h"
#include "LCD.h"
#include "Keypad.h"
#include "COM.h"
#include "NET.h"
#include "MQTT.h"
#include "Software.h"

void setup()
{
    COM::Init();
    LCD::Init();
    Keypad::Init();
    WindSpeed::Init();
    WindDirection::Init();
    NET::Init();
    MQTT::Init();
    Software::Init();
}

void loop()
{
    MQTT::POST(); Keypad::Exec(); delay(hz2millis(1));
}
