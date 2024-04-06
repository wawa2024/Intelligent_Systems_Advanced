/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#include <avr/interrupt.h>

#define DHCP
#define NET
#define KEYPAD
#define DEBUG_MQTT

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
}

void loop()
{
    WindDirection::Update();
    WindSpeed::Update();

#ifdef NET
    MQTT::POST(); 
#endif

#ifdef KEYPAD
    Keypad::Exec(); 
#endif 

    delay(seconds2millis(1));
}
