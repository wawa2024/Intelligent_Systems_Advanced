#ifndef MusicPlayer_h
#define MusicPlayer_h

#include "Arduino.h"

class MusicPlayer 
{
  public:
    void playSong(Note song_name[], size_t song_length);
  private:
    uint8_t pin;
    uint8_t led_pin;
    uint32_t whole_note;
    uint32_t previousMillis = 0;
    void setTempo(uint32_t value);
    void playNote(uint8_t pin, uint16_t frequency, float division);
};

#endif