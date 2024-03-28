/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#define DHCP
#define DEBUG

#include "Utils.h"
#include "COM.h"
#include "NET.h"
#include "LCD.h"
#include "WindDirection.h"
#include "WindSpeed.h"
#include "MQTT.h"

#ifdef KEYPAD
#include "Keypad.h"
#endif

#include "Software.h"

void setup()
{
    COM::Init();
    NET::Init();
    LCD::Init();

    WindSpeed::Init();
    WindDirection::Init();

    //Keypad::Init();
    //Software::Init();
}

void loop()
{
    WindSpeed::Update();
    WindDirection::Update();

    Software::VARstats();

    MQTT::POST(); 

    #ifdef KEYPAD
    Keypad::Exec(); 
    #endif 

    delay(seconds2millis(10));
}
