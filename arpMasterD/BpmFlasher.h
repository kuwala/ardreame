#ifndef BPMFLASHER_H
#define BPMFLASHER_H
#include <Arduino.h>
#include "Bpm.h"
#include "BpmUtil.h"

class BpmFlasher {
  private:
    BFSM state;
    NOTE_LEN flashNoteLen;
    unsigned long timer;
    int restTime;
    int playTime;
    int pin1, pin2;
    Bpm * bpmPtr;
  public:
    BpmFlasher(Bpm * bpmPtr);
    void update();
    //void setPins(int pin1, int pin2);

};



#endif
