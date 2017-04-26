#include "notes.h"
byte transpose = 0;
byte scale = 0;
#define SCALE_COUNT   16
#define SCALE_LENGTH 7
//given matrix position, get the scale step
const byte matrix_to_scale_step[GRID_SIZE]=
{   
  3,4,5,6,0,1,2,3,
  0,1,2,3,4,5,6,0,
  3,4,5,6,0,1,2,3,
  0,1,2,3,4,5,6,0,
  3,4,5,6,0,1,2,3,
  0,1,2,3,4,5,6,0,
  3,4,5,6,0,1,2,3,
  0,1,2,3,4,5,6,0
};
//given matrix position, get the octave 
const byte matrix_to_octave[GRID_SIZE]=
{   
  3,3,3,3,4,4,4,4,
  3,3,3,3,3,3,3,4,
  2,2,2,2,3,3,3,3,
  2,2,2,2,2,2,2,3,
  1,1,1,1,2,2,2,2,
  1,1,1,1,1,1,1,2,
  0,0,0,0,1,1,1,1,
  0,0,0,0,0,0,0,1
};
const byte scales [SCALE_COUNT][SCALE_LENGTH] = 
{
  //heptatonia Prima
  {0,2,4,5,7,9,11},  //ionian
  {0,2,3,5,7,9,10},  //dorian
  {0,1,3,5,7,8,10},  //phyrgian
  {0,2,4,6,7,9,11},  //lydian
  {0,2,4,5,7,9,10},  //Mixolydian
  {0,2,3,5,7,8,10},  // Aeolian
  {0,1,3,5,6,8,10}, //Locrain
  {0,2,3,5,7,8,11},  // Harmonic Minor
  //heptatonia Secunda
  {0,2,4,5,7,8,10},  // major minor scale 
  {0,2,3,5,7,9,11},  // Melodic Minor
  {0,1,3,5,7,9,10},  // phyrgian raised 6th
  {0,2,4,6,8,9,11},  // lydian raised 5th 
  {0,2,4,6,7,9,10},  // lydian dominant
  {0,2,4,5,6,8,10}, //Locrain sharp 2 - half diminished
  {0,1,3,4,6,8,10}, //Locrain diminished 4- altered
  //others
  {0,1,3,5,7,8,11}  //neapolitan minor
};

//converts a matrix location to an actual midi note number
byte get_note_number( const byte button )
{
  const byte scale_step = matrix_to_scale_step[button];
  byte note = matrix_to_octave[button] * 12;
  note += scales[scale][scale_step];
  note += transpose;
  while (note > 60)
    note -= 12;
  return note;
}
