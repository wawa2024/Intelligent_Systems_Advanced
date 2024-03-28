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
#include "Keypad.h"
#include "MQTT.h"
#include "Software.h"

void setup()
{
    noInterrupts();
    COM::Init();
    NET::Init();
    LCD::Init();

    WindSpeed::Init();
    WindDirection::Init();

    Keypad::Init();
    MQTT::Init();
    Software::Init();
    interrupts();
}

void loop()
{
    MQTT::POST(); Keypad::Exec(); delay(seconds2millis(1));
}
