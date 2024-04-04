#ifndef MusicPlayer_h
#define MusicPlayer_h

#include "Arduino.h"


static void playSong();
uint8_t pin;
uint32_t whole_note;
uint32_t previousMillis;
void setTempo(uint32_t value);
void playNote(uint8_t pin, uint16_t frequency, float division);



#endif