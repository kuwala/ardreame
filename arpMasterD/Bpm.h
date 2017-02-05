#ifndef BPM_H
#define BPM_H
#include <Arduino.h>
#include "BpmUtil.h"

class Bpm {
  private:
    float bpm;
    int bpmCount; // what beat are you on?
    // Time 4 / 4
    NOTE_LEN bpmTop;
    int bpmBottom;
    
    int stepDelay;
    int stepCount;
    
    BFSM state;
    unsigned long timer;
    int timeDelay;
  
  public:
    Bpm();
    void setTimeSig(NOTE_LEN top, int bottom);
    void setBpm(float bpm);
    float getBpm();
    void update();
    
    int getStepDelay();
    int getBeat(); // returns count
    
    
    

};

#endif
