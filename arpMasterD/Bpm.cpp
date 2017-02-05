#include "Bpm.h"
#include <Arduino.h>

Bpm::Bpm() {
  bpm = 30;
  bpmCount = 0;
  // Time 4 / 4
  bpmTop = QUARTER;
  bpmBottom = 4;
  timer = 0;
  timeDelay = 0;
  state = BPLAY;
  
};
void Bpm::setBpm(float bpm) {
  this->bpm = bpm;
};

float Bpm::getBpm() {
  return bpm;
};

void Bpm::setTimeSig(NOTE_LEN top, int bottom) {
  bpmTop = top;
  bpmBottom = bottom;
};

int Bpm::getStepDelay() {
  
  //returns 1/32nd
  return ( ( 7.5 / bpm) * 1000 );
};
int Bpm::getBeat() {
  return bpmCount;
};

void Bpm::update() {
  switch(state) {
  
    case BPLAY:
      bpmCount = stepCount / 4;
      bpmCount = bpmCount % bpmBottom;
      
      //Serial.println(bpmCount );
      timeDelay = getStepDelay();
      state = BREST;
      break;
    
   case BREST:
    if ((millis() - timer) > timeDelay) {
     // Serial.print("step coubnt:");
      //Serial.println(bpmCount);
      stepCount ++;
      state = BPLAY;
      timer = millis();
    }

    
  } // end switch
  
};



