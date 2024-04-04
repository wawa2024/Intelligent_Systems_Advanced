namespace MusicPlayer 
{
  #include "Song.h"
  #include "Pitches.h"

  uint8_t pin = 6;
  uint32_t whole_note = 4*60/100*1000;
  uint32_t previousMillis = 0;

  void setTempo(uint32_t value) {
    whole_note = 4*60/value*1000;
  }

  void playNote(uint8_t pin, uint16_t frequency, float division) {
    uint32_t duration = whole_note / division;

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
    setTempo(in_your_face[0].frequency);
    uint16_t repetitions = in_your_face[0].repetitions;
    size_t song_length = sizeof(in_your_face) / sizeof(Note);

    for (int times_played = 0; times_played < repetitions; times_played++) {
      for (int note_index = 1; note_index < song_length; note_index++) {
        // 0 index used for metadata ^
        for (int repeat_note = 0; repeat_note < in_your_face[note_index].repetitions; repeat_note++) {
          playNote(pin, in_your_face[note_index].frequency, in_your_face[note_index].division);
        }
      }
    }
  }

}
