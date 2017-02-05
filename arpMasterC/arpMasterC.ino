#include "globalVars.h"
#include "pitches.h"

void playNote(int noteDuration, int notePitch) {
  int playTime = noteDuration * 0.75;
  int restTime = noteDuration * 0.25;
  
  Serial.println("Note Duration, PlayTime, RestTime");
  //Serial.println(noteDuration);
  Serial.println(playTime);
  Serial.println(restTime);
  
  tone(piezoPin, notePitch);
  delay(playTime);
  noTone(piezoPin);
  delay(restTime);
}
void bpmFlasherUpdate() {
  
  if(bpmFlasherState == BPLAY) {
    
    if ((millis() - bpmFlasherTimer) > bpmFlasherRestTime) {
      Serial.println("flasher Play");
      bpmFlasherTimer = millis();
      //keeps count from going over
      bpmCount = bpmCount % bpmBottom;
      
      
      int flashLen = getNoteDuration(bpmLEDNote, bpm);
      // led on for 1/4 the bpmLEDNote length
      bpmFlasherPlayTime = flashLen * 0.25; 
      bpmFlasherState = BREST;
      
      if(bpmCount == 0) {
        digitalWrite(ledPinBlue, HIGH);
      } else {
        digitalWrite(ledPinRed, HIGH);
      }
    } // end timer
    
  } else if (bpmFlasherState == BREST) {
    if ((millis() - bpmFlasherTimer) > bpmFlasherPlayTime) {
      Serial.println("flasher rest");
      bpmFlasherTimer = millis();
      //update count
      bpmCount ++;
      //gets flash Length based on bpm and default bpmLEDNote ( quartor note )
      int flashLen = getNoteDuration(bpmLEDNote, bpm);
      // rests for 3/4 the bpmLEDNote length
      bpmFlasherRestTime = flashLen * 0.75; 
      bpmFlasherState = BPLAY;
      
         digitalWrite(ledPinBlue, LOW);
         digitalWrite(ledPinRed, LOW);
       
    }  //end timer
  } // end if bpmFlasherState 
}



void playMelody() {
  if (melodyState == BREST ) {
   if( (millis() - melodyTimer) > noteRestTime){
     //calculate note_duration
     int noteDuration = 0;
     int notePitch = 0;
     
     noteDuration = getNoteDuration( noteLens[melodyCount], bpm);
     //Steps through all the notes in the melody
     melodyCount = melodyCount % melodyLen;
     
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
     noteOnTime = noteDuration * 0.75;
     //notePitch = notePitches[melodyCount];
     //playNote(noteDuration, notePitch);
     notePitch = noteTravel();
     noteOn(notePitch);
     melodyCount ++;
     melodyTimer = millis();
     melodyState = BPLAY;
   }
  } else if (melodyState == BPLAY) {
    if ( (millis() - melodyTimer) > noteOnTime ) {
      noteOff();
      
      int noteDuration = getNoteDuration( noteLens[melodyCount], bpm);
      noteRestTime = noteDuration * 0.25;
      
      melodyState = BREST;
      melodyTimer = millis();
    }
    
  }
}

void noteOn(int pitch) {
  tone(piezoPin, pitch);
}
void noteOff() {
  noTone(piezoPin);
}

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
     Serial.println("yoooo" + String(duration));
     break;
   case SIXTEENTH:
     duration = ( 15 / bpm )* 1000;
     break;
   default:
     break;    
  }
  return duration;
}


void setup() {
  Serial.begin(9600);
  
  pinMode(ledPinBlue, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  
  pinMode(but1, INPUT);
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  
  
  
  
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
  bpmFlasherUpdate();
  playMelody();
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
  } 
  
  
}
