#include "BpmUtil.h"

namespace BpmUtil {
  
  int getNoteDuration(NOTE_LEN noteLen, float bpm) {
    int duration = 0;
    switch (noteLen) {
     case WHOLE:
       duration = ( 240 / bpm )* 1000;
       break;
     case HALF:
       duration = ( 120 / bpm )* 1000;
       break;
     case QUARTER:
       duration = ( 60 / bpm )* 1000;
       break;
     case EIGTH:
       duration = ( 30 / bpm )* 1000;
       break;
     case SIXTEENTH:
       duration = ( 15 / bpm )* 1000;
       break;
     case THIRTYSECOND:
       duration = ( 7.5 / bpm)* 1000;
     default:
       break;    
    }
    return duration;
  }

} // end namespace
