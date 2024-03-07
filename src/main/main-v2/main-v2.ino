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

void Draw(void)
{
    display.lcd -> clear();
    display.lcd -> print("WindDirection: ");
    display.lcd -> print(WindDirection::Value());

}

struct Info
{
    int GetRam(void)
    {
        extern int __heap_start, *__brkval;
        int v;
        return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
    }
    void PrintRam(void)
    {
        Serial.print("Arduino::RAM: ");
        Serial.println(GetRam());
    }
    Info(){ Serial.begin(baud_rate); PrintRam(); }
    ~Info(){ PrintRam(); }
};

void setup()
{
    Info observer; 
    WindSpeed::Init();
    WindDirection::Init();
}

void loop()
{
    PrintStats();
    Draw();
	delay(refresh_rate);
}
