/******************************************************************************
 * File: ./main-v2.ino
 ******************************************************************************/
#include "Keypad.h"
#include "LCD.h"
#include "WindDirection.h"
#include "WindSpeed.h"

static const int     
        refresh_rate=       1000,
        baud_rate=          9600
        ;

void PrintStats(void)
{
    WindDirection::Print();
    WindSpeed::Print();
}

void setup()
{
    Serial.begin(baud_rate);
    WindSpeed::Init();
    WindDirection::Init();
}

void loop()
{
    PrintStats();
	delay(refresh_rate);
}
