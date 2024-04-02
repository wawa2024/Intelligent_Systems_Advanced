/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#define DHCP
#define NET
//#define DEBUG
#define KEYPAD

#include "IO.h"
#include "Utils.h"

#include "COM.h"
#include "LCD.h"
#include "WindDirection.h"
#include "WindSpeed.h"

#ifdef NET
    #include "NET.h"
    #include "MQTT.h"
#endif

#ifdef KEYPAD
    #include "Keypad.h"
#endif

#include "Software.h"

void setup()
{
    COM::Init();
    LCD::Init();

#ifdef NET
    NET::Init();
#endif

    WindSpeed::Init();
    WindDirection::Init();

#ifdef KEYPAD
    Keypad::Init();
#endif

    Software::Init();

    Wait(3);
}

void loop()
{
#ifdef NET
    MQTT::POST(); 
#endif
#ifdef KEYPAD
    Keypad::Exec(); 
#endif 
    WindDirection::Update();
    WindSpeed::Update();

    delay(seconds2millis(1));
}
