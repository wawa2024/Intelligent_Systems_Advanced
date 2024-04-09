#include "Pitches.h"

struct Note;

struct Note {
  uint16_t frequency;
  uint16_t duration;
  uint8_t repetitions;
};

Note grace[] = {
  {100, 1, 1},
  {NOTE_CS4, 75, 1},
  {NOTE_E4, 900, 1},
  {NOTE_GS4, 300, 1},
  {NOTE_FS4, 150, 1},
  {NOTE_GS4, 150, 1},
  {NOTE_FS4, 150, 1},
  {NOTE_E4, 150, 1},
  {NOTE_GS4, 300, 1},
  {NOTE_CS4, 300, 1},
  {NOTE_E4, 300, 1},
  {NOTE_FS4, 300, 1},
  {NOTE_FS4, 300, 1},
  {NOTE_GS4, 300, 1},
  {NOTE_GS4, 300, 1},
  {NOTE_GS3, 300, 1},
  {NOTE_GS3, 300, 1},
  {NOTE_CS4, 300, 1},
  {NOTE_CS4, 900, 1},

  {NOTE_FS4, 300, 1},
  {NOTE_GS4, 150, 1},
  {NOTE_FS4, 150, 1},
  {NOTE_E4, 150, 1},
  {NOTE_FS4, 150, 1},
  {NOTE_E4, 150, 1},
  {NOTE_DS4, 150, 1},
  {NOTE_CS4, 150, 1},
  {NOTE_E4, 150, 1},
  {NOTE_DS4, 150, 1},
  {NOTE_CS4, 150, 1},
  {NOTE_B3, 150, 1},
  {NOTE_DS4, 150, 1},
  {NOTE_CS4, 150, 1},
  {NOTE_B3, 150, 1},
  {NOTE_A3, 150, 1},
  {NOTE_CS4, 150, 1},
  {NOTE_B3, 150, 1},
  {NOTE_A3, 150, 1},
  {NOTE_GS3, 150, 1},
  {NOTE_B3, 150, 1},
  {NOTE_A3, 150, 1},
  {NOTE_GS3, 150, 1},
  {NOTE_FS3, 150, 1},
  {NOTE_E3, 150, 1},

  {NOTE_A3, 900, 1},
  {NOTE_A3, 300, 1},
  {NOTE_GS3, 225, 1},
  {NOTE_A3, 225, 1},
  {NOTE_GS3, 225, 1},
  {NOTE_FS3, 300, 1},
  {NOTE_GS3, 300, 1},
  {NOTE_FS3, 300, 1},
  {NOTE_FS3, 300, 1},
  {NOTE_E3, 300, 1},
  {NOTE_E3, 300, 1},
  {NOTE_FS3, 300, 1},
  {NOTE_FS3, 150, 1},
  {NOTE_GS3, 150, 1},
  {NOTE_FS3, 300, 1},
  {NOTE_E3, 300, 1},
  {NOTE_B2, 300, 1},
  {NOTE_CS3, 2400, 1}
};