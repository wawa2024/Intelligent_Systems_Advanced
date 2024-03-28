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
//#include "MQTT.h"
#include "MQTT2.h"
#include "Software.h"

void setup()
{
    fetchIP();
    COM::Init();
    LCD::Init();
    Keypad::Init();
    WindSpeed::Init();
    WindDirection::Init();
    NET::Init();
    //MQTT::Init();
    Software::Init();
}

void loop()
{
    //MQTT::POST();
    send_MQTT_message(); Keypad::Exec(); delay(hz2millis(5));
}
