/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#define NoDebug
#define MQTT2

#include "Utils.h"
#include "WindDirection.h"
#include "WindSpeed.h"
#include "LCD.h"
#include "Keypad.h"
#include "COM.h"

#ifdef MQTT
  #include "NET.h"
  #include "MQTT.h"
#else
  #include "MQTT2.h"
#endif

#include "Software.h"
unsigned long lastMillis = 0;

void setup()
{
    COM::Init();
    LCD::Init();
    Keypad::Init();
    WindSpeed::Init();
    WindDirection::Init();
    Software::Init();
#ifdef MQTT
    NET::Init();
    MQTT::Init();
#else
    fetch_IP();
#endif
}

void loop()
{
  #ifdef MQTT
    MQTT::POST();
  #else
    if(millis() - lastMillis >= 10000){
      send_MQTT_message();
      lastMillis = millis();
    }
  #endif 

    Keypad::Exec();
    delay(50);
}
