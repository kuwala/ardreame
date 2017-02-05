#ifndef NOTE_H
#define NOTE_H
#include <Arduino.h>

class Note {
  public:
    int semitone; // 0 = rest 
    int duration; // 1, 2, 4, 8, 16, 32, 64
    
    Note() {
      semitone = 0;
      duration = 16;
    }
    boolean isItRest() {
      if( 0 == semitone) {
        return true;
      } else {
        return false;
      }
    }

};


#endif
