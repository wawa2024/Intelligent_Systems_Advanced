#include "Pitches.h"

struct Note;

struct Note {
  uint16_t frequency;
  float division;
  uint8_t repetitions;
};

Note in_your_face[] = {
  {140, 1, 2},
  {NOTE_C3, 8, 4}, 
  {0, 8, 1},
  {NOTE_C3, 8, 6}, 
  {0, 8, 1},
  {NOTE_C3, 8, 2}, 
  {0, 8, 2},
  {NOTE_C3, 8, 4}, 
  {0, 8, 1},
  {NOTE_C3, 8, 1}, 
  {0, 8, 1},
  {NOTE_C3, 8, 1}, 
  {0, 8, 1},
  {NOTE_C3, 8, 5}, 
  {0, 8, 2}
};