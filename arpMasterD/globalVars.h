#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include <Arduino.h>
#include "pitches.h"
#include "Bpm.h"
#include "BpmFlasher.h"

Bpm travisBpm;
BpmFlasher bpmFlasher(&travisBpm);

BFSM melodyState = BPLAY;

/*
enum NOTE_LEN {
  WHOLE,
  HALF,
  QUARTER,
  EIGTH,
  SIXTEENTH
}; */

unsigned long timer;
int timeDelay = 80;


unsigned long melodyTimer;
int noteOnTime = 0;
int noteRestTime = 0;



int noteTravelerCount = -9;
float noteTravelStep = 3;
int noteTravelerMax = 36;
int noteTravelerMin = -36;
int noteTravelerDir = 1;

//bpm can /should be turned into an object
int bpmTravelLimit = 90;
int bpmTravelDirection = 1;
int bpmTravelCount = 0;
int bpmTravelRate = 1;


float beatDuration = 0; //getNoteDuration(bpmTop, bpm); // in mill seconds
NOTE_LEN bpmLEDNote = QUARTER; // on time played like note

const int melodyLen = 4; // needs to be the same for melody NoteLen and Pitches
int melodyCount = 0;
NOTE_LEN noteLens[melodyLen] = { QUARTER, QUARTER, QUARTER, QUARTER };
//NOTE_LEN noteLens[] = { QUARTER, EIGTH, SIXTEENTH, SIXTEENTH, QUARTER, EIGTH, SIXTEENTH, SIXTEENTH};
//NOTE_LEN noteLens[] = { SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH, SIXTEENTH};
int notePitches[melodyLen] = { NOTE_C4, NOTE_E4, NOTE_G4, NOTE_A4};




int ledPinBlue = 13;
int ledPinRed = 12;
int piezoPin = 8;
int but1 = 7;
int but1Val = 0;
int pot1 = A0;
int pot2 = A1;
int pot1Val = 0;
int pot2Val = 0;




#endif

