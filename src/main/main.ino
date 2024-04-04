/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#define DHCP
#define NET
#define KEYPAD

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
    #include "Software.h"
#endif


void setup()
{
    COM::Init();
    LCD::Init();

#ifdef NET
    NET::Init();
    MQTT::Init();
#endif

    WindSpeed::Init();
    WindDirection::Init();

#ifdef KEYPAD
    Keypad::Init();
    Software::Init();
#endif

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

    Keypad::ScanKeys();
}
