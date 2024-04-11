namespace MusicPlayer 
{
  #include "Song.h"
  #include "Pitches.h"

  uint8_t pin = 6;
  uint16_t index = 0;
  uint16_t repetitions = grace[0].duration;
  size_t song_length = sizeof(grace) / sizeof(Note);
  uint16_t delay_music = 0;
  uint8_t execution_phase = 0;

  void playNote(uint8_t pin, uint16_t frequency, uint16_t duration) {
    uint16_t actualDuration = duration * 0.9;

    switch (execution_phase) {
      case 0:
        if (frequency > 0) {
          tone(pin, frequency, actualDuration);
        }
        delay_music = duration * 0.9;
        break;
      case 2:
        delay_music = duration - actualDuration;
        break;
      default:
        delay_music = 0;
        execution_phase = 0;
        index++;
        break;
    }
  }

  void play() {
    if (millis() - IO::lastMillis >= delay_music) {
      if (index >= song_length) {
        IO::keepPlaying = false;
      } else {
        playNote(pin, grace[index].frequency, grace[index].duration);
      }
    }
  }
/*
  void playSong(uint32_t lastMillis) {
    uint16_t repetitions = grace[0].duration;
    size_t song_length = sizeof(grace) / sizeof(Note);

    for (int times_played = 0; times_played < repetitions; times_played++) {
      for (int note_index = 1; note_index < song_length; note_index++) {
        // 0 index used for metadata ^
        playNote(pin, grace[note_index].frequency, grace[note_index].duration, lastMillis);
      }
    }
  }
}
*/
