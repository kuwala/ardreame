#ifndef BPMUTIL_H
#define BPMUTIL_H

//used for fsm
enum BFSM {
  BPLAY,
  BREST,
  BPLAYDELAY,
  BRESTDELAY,
  BUPDATE
};

//Needs to be converted to NOTE_WHOLE and such
enum NOTE_LEN {
  WHOLE,
  HALF,
  QUARTER,
  EIGTH,
  SIXTEENTH,
  THIRTYSECOND
};

namespace BpmUtil {
  int getNoteDuration(NOTE_LEN noteLen, float bpm);
  
}

#endif
