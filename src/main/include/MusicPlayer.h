namespace MusicPlayer 
{
  #include "Song.h"

  uint8_t pin = 6;
  uint32_t previousMillis = 0;

  void playNote(uint8_t pin, uint16_t frequency, uint16_t duration) {
    uint32_t actualDuration = duration * 0.9;
    
    if (frequency > 0) {
      tone(pin, frequency, actualDuration);
    }
    delay(actualDuration);
    previousMillis = millis();
    delay(duration - actualDuration);
    previousMillis = millis();
  }

  void playSong() {
    uint16_t repetitions = grace[0].duration;
    size_t song_length = sizeof(grace) / sizeof(Note);

    for (int times_played = 0; times_played < repetitions; times_played++) {
      for (int note_index = 1; note_index < song_length; note_index++) {
        // 0 index used for metadata ^
        playNote(pin, grace[note_index].frequency, grace[note_index].duration);
      }
    }
  }
}