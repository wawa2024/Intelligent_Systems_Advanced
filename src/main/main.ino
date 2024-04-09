/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#define DHCP
#define NET
#define KEYPAD

#include "Utils.h"
#include "IO.h"

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

    delay(3000);
}

void loop()
{
#ifdef NET
#ifdef MQTT
    MQTT::POST(); 
#endif
#endif

    WindDirection::Update();
    WindSpeed::Update();

    Software::Exec(); 
    Keypad::ScanKeys();
    delay(1000);
}
