#include "BpmFlasher.h"
#include <Arduino.h>

BpmFlasher::BpmFlasher(Bpm * bpmPtr) {
  flashNoteLen = QUARTER;
  state = BPLAY;
  timer = 0;
  pin1 = 13;
  pin2 = 12;
  restTime = 0;
  playTime = 0;
  this->bpmPtr = bpmPtr;
};

void BpmFlasher::update() {
  
  if(state == BPLAY) {
    
    if ((millis() - timer) > restTime) {
      timer = millis();
      //keeps count from going over
      int bpmCount = bpmPtr->getBeat();
      int bpm = bpmPtr->getBpm();
      //bpmCount = bpm->getCount();
      
      
      int flashLen = BpmUtil::getNoteDuration(flashNoteLen, bpm);
      // led on for 1/4 the bpmLEDNote length
      playTime = flashLen * 0.25; 
      state = BREST;
      
      if(bpmCount == 0) {
        digitalWrite(pin1, HIGH);
      } else {
        digitalWrite(pin2, HIGH);
      }
      Serial.print("Flash On millis: ");
     Serial.println(millis());
     Serial.print("flashers bpmCoubnt  ");
      Serial.println(bpmCount);
      Serial.println("");
    } // end timer
    
  } else if (state == BREST) {
    if ((millis() - timer) > playTime) {
      
      timer = millis();
      
      float bpm = bpmPtr->getBpm();
      //gets flash Length based on bpm and default bpmLEDNote ( quartor note )
      int flashLen = BpmUtil::getNoteDuration(flashNoteLen, bpm);
      // rests for 3/4 the bpmLEDNote length
      restTime = flashLen * 0.75; 
      state = BPLAY;
      
         digitalWrite(pin1, LOW);
         digitalWrite(pin2, LOW);
       
    }  //end timer
  } // end if bpmFlasherState 
  
};
