#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include <Arduino.h>
#include "pitches.h"

enum BFSM {
  BPLAY,
  BREST
};

BFSM melodyState = BPLAY;

enum NOTE_LEN {
  WHOLE,
  HALF,
  QUARTER,
  EIGTH,
  SIXTEENTH
};

unsigned long timer;
int timeDelay = 80;

unsigned long bpmTimer;
int bpmTimeDelay = 0;
int bpmPlayDelay = 0;
int bpmRestDelay = 0;

unsigned long melodyTimer;
int noteOnTime = 0;
int noteRestTime = 0;

BFSM bpmFlasherState = BPLAY; //BPLAY or BREST
unsigned long bpmFlasherTimer;
int bpmFlasherRestTime = 0;
int bpmFlasherPlayTime = 0;


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

float bpm = 100;
int bpmCount = 0; // what beat are you on?

//  4 / 4 Time
NOTE_LEN bpmTop = QUARTER; 
int bpmBottom = 4; 

float beatDuration = 0; //getNoteDuration(bpmTop, bpm); // in mill seconds
NOTE_LEN bpmLEDNote = EIGTH; // on time played like note

int melodyLen = 5;
int melodyCount = 0;
//NOTE_LEN noteLens[] = { QUARTER, QUARTER, QUARTER, QUARTER };
//NOTE_LEN noteLens[] = { QUARTER, EIGTH, SIXTEENTH, SIXTEENTH, QUARTER, EIGTH, SIXTEENTH, SIXTEENTH};
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




#endif

