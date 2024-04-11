/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#define DHCP
#define NET
#define KEYPAD
#define DEBUG

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

//    IO::lastMillis = millis() + 2000; doesn't work
    delay(2000);
}

void loop()
{
    
    if (millis() - IO::lastMillis >= 1000) {
        IO::lastMillis = millis();

    #ifdef NET
        MQTT::POST(); 
    #endif

        WindDirection::Update();
        WindSpeed::Update();

        Software::Exec(); 
    }

    Keypad::ScanKeys();
}
