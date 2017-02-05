#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include <Arduino.h>
#include "pitches.h"

enum NOTE_LEN {
  WHOLE,
  HALF,
  QUARTER,
  EIGTH,
  SIXTEENTH
};

//bpm can /should be turned into an object
int bpmTravalLimit = 80;
int bpmTravelDirection = 1;
int bpmTravelCount = 0;

float bpm = 140;
int bpmCount = 0; // what beat are you on?

//  4 / 4 Time
NOTE_LEN bpmTop = QUARTER; 
int bpmBottom = 4; 

float beatDuration = 0; //getNoteDuration(bpmTop, bpm); // in mill seconds
NOTE_LEN bpmLEDNote = EIGTH; // on time played like note

int melodyLen = 5;
int melodyCount = 0;
//NOTE_LEN noteLens[] = { QUARTER, QUARTER, QUARTER, QUARTER };
//NOTE_LEN noteLens[] = { QUARTER, EIGTH, EIGTH, QUARTER, QUARTER};
NOTE_LEN noteLens[] = { SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH};
int notePitches[] = { NOTE_C4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4};




int ledPinBlue = 13;
int ledPinRed = 12;
int piezoPin = 8;
int but1 = 7;
int but1Val = 0;
int pot1 = A0;
int pot2 = A1;
int pot1Val = 0;
int pot2Val = 0;


unsigned long timer;
int timeDelay = 100;;

#endif

