#include "Pitches.h"

struct Note;

struct Note {
  uint16_t frequency;
  float division;
  uint8_t repetitions;
};

Note grace[] = {
  {100, 1, 1},
  {NOTE_CS4, 32, 1},
  {NOTE_E4, 4/1.5, 1},
  {NOTE_GS4, 8, 1},
  {NOTE_FS4, 16, 1},
  {NOTE_GS4, 16, 1},
  {NOTE_FS4, 16, 1},
  {NOTE_E4, 16, 1},
  {NOTE_GS4, 8, 1},
  {NOTE_CS4, 8, 1},
  {NOTE_E4, 8, 1},
  {NOTE_FS4, 8, 1},
  {NOTE_FS4, 8, 1},
  {NOTE_GS4, 8, 1},
  {NOTE_GS4, 8, 1},
  {NOTE_GS3, 8, 1},
  {NOTE_GS3, 8, 1},
  {NOTE_CS4, 8, 1},
  {NOTE_CS4, 4/1.5, 1},

  {NOTE_FS4, 8, 1},
  {NOTE_GS4, 16, 1},
  {NOTE_FS4, 16, 1},
  {NOTE_E4, 16, 1},
  {NOTE_FS4, 16, 1},
  {NOTE_E4, 16, 1},
  {NOTE_DS4, 16, 1},
  {NOTE_CS4, 16, 1},
  {NOTE_E4, 16, 1},
  {NOTE_DS4, 16, 1},
  {NOTE_CS4, 16, 1},
  {NOTE_B3, 16, 1},
  {NOTE_DS4, 16, 1},
  {NOTE_CS4, 16, 1},
  {NOTE_B3, 16, 1},
  {NOTE_A3, 16, 1},
  {NOTE_CS4, 16, 1},
  {NOTE_B3, 16, 1},
  {NOTE_A3, 16, 1},
  {NOTE_GS3, 16, 1},
  {NOTE_B3, 16, 1},
  {NOTE_A3, 16, 1},
  {NOTE_GS3, 16, 1},
  {NOTE_FS3, 16, 1},
  {NOTE_E3, 16, 1},

  {NOTE_A3, 4/1.5, 1},
  {NOTE_A3, 8, 1},
  {NOTE_GS3, 16*3/2, 1},
  {NOTE_A3, 16*3/2, 1},
  {NOTE_GS3, 16*3/2, 1},
  {NOTE_FS3, 8, 1},
  {NOTE_GS3, 8, 1},
  {NOTE_FS3, 8, 1},
  {NOTE_FS3, 8, 1},
  {NOTE_E3, 8, 1},
  {NOTE_E3, 8, 1},
  {NOTE_FS3, 8, 1},
  {NOTE_FS3, 16, 1},
  {NOTE_GS3, 16, 1},
  {NOTE_FS3, 8, 1},
  {NOTE_E3, 8, 1},
  {NOTE_B2, 8, 1},
  {NOTE_CS3, 1, 1}
};