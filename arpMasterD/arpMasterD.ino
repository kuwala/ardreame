#include "globalVars.h"
#include "pitches.h"
#include "Bpm.h"
#include "BpmUtil.h"

void setup() {
  Serial.begin(9600);
  Serial.println("@kuwala");
  pinMode(ledPinBlue, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  
  pinMode(but1, INPUT);
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  
}

void stepMelody() {
  melodyCount ++;
  melodyCount = melodyCount % melodyLen;
}
  
void playMelody() {
  switch (melodyState) 
  {
    case BREST:
    { // wrap case block in {} to allow intializations of variables
      noteOff();
      int noteDuration = BpmUtil::getNoteDuration( noteLens[melodyCount], travisBpm.getBpm());
      noteRestTime = noteDuration * 0.25;
      melodyState = BRESTDELAY;
      melodyTimer = millis();
      break;
    }
    case BPLAY:
    {
       Serial.print("melody count ");
       Serial.println(melodyCount);
       
       int noteDuration = BpmUtil::getNoteDuration( noteLens[melodyCount], travisBpm.getBpm());                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
       noteOnTime = noteDuration * 0.75;
       //notePitch = notePitches[melodyCount];
       //playNote(noteDuration, notePitch);
       int notePitch = 440; //noteTravel();
       noteOn(notePitch);
       Serial.print("Note On millis: ");
       Serial.println(millis());
       
       melodyTimer = millis();
       melodyState = BPLAYDELAY;
       
      break;
    }
    case BPLAYDELAY:
      if ( (millis() - melodyTimer) > noteOnTime ) {
        melodyState = BREST;
      }
      break;
    case BRESTDELAY:
      if( (millis() - melodyTimer) > noteRestTime){
        melodyState = BUPDATE;
      }
      break;
    case BUPDATE:
      melodyCount ++;
      melodyCount = melodyCount % melodyLen;
      melodyState = BPLAY;
    
      break;
    default:
      break;
      
  } // end switch
} // end function

void noteOn(int pitch) {
  tone(piezoPin, pitch);
}
void noteOff() {
  noTone(piezoPin);
}





int notePitchCalc(int n) {
  //n is halfsteps above A4;
  
  //fn = f0 * (a)^n 
  //fo = 440hz // which is A4 above middle C
  //a = (2)1/12 = 1.059463094359
  float a = 1.059463094359;
  
  return 440 * pow(a, n);  
}
int noteTravel() {
  if (noteTravelerCount > noteTravelerMax) {
    noteTravelerDir *= -1;    
  } else if (noteTravelerCount < noteTravelerMin) {
    noteTravelerDir *= -1;    
  }
  noteTravelerCount += noteTravelerDir * noteTravelStep;  
  Serial.print("noteTravel count:");
  Serial.println(notePitchCalc(noteTravelerCount));
  return notePitchCalc(noteTravelerCount); 
}

void loop() {
  //bpmFlasherUpdate();
  travisBpm.update();
  playMelody();
  bpmFlasher.update();
//tone(piezoPin,340);
  //delay(500);
  //noTone(piezoPin);
  //delay(200);
  //bpmFlasherUpdate();
  //countBeats();
  //delay(10000);
  
  /*
  //Button and Pots
  but1Val = digitalRead(but1);
  pot1Val = analogRead(pot1);
  pot2Val = analogRead(pot2);
  */
  
  //pot1Val = map( pot1Val , 0, 1023, 0, 127);
  
  /*
  if ( (millis() - timer) > timeDelay) {
    if(bpmTravelDirection == 1) {
      bpm += bpmTravelRate;
      bpmTravelCount+= bpmTravelRate;
    } else {
      bpm -= bpmTravelRate;
      bpmTravelCount-= bpmTravelRate;
    }
    if (abs(bpmTravelCount) > bpmTravelLimit) {
      bpmTravelDirection = bpmTravelDirection * -1;
    }
    Serial.print("bpm: ");
    Serial.println(bpm);
    timer = millis();
  } */
  
  
}
