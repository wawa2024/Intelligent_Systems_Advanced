/******************************************************************************
 * File: ./main.ino
 ******************************************************************************/
#define DHCP
#define NET
#define KEYPAD
#define DEBUG
#define MUSICPLAYER

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

uint32_t lastMillis = 0;

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
    if (millis() - lastMillis >= 1000) {
        lastMillis = millis();
    #ifdef NET
        MQTT::POST(); 
    #endif

        WindDirection::Update();
        WindSpeed::Update();

        Software::Exec(lastMillis); 
    }

    // possible call to music player if playmusic boolean flag is changed to true with keypad press
    if (MusicPlayer::keepPlaying) {  MusicPlayer::play();  }

    Keypad::ScanKeys();
}
