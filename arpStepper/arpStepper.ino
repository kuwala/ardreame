#include "globalVars.h"
#include "pitches.h"

void playNote(int noteDuration, int notePitch) {
  int playTime = noteDuration * 0.75;
  int restTime = noteDuration * 0.25;
  
  Serial.println(noteDuration);
  Serial.println(playTime);
  Serial.println(restTime);
  
  tone(piezoPin, notePitch);
  delay(playTime);
  noTone(piezoPin);
  delay(restTime);
}
void flashLed(int count) {
  int flashLen = getNoteDuration(bpmLEDNote, bpm);
  beatDuration = getNoteDuration(bpmTop, bpm);
  int playLen = flashLen * 0.25;
  int restLen = flashLen * 0.75;
  
  if(bpmCount == 0) {
    digitalWrite(ledPinBlue, HIGH);
    delay(playLen);
    digitalWrite(ledPinBlue, LOW);
    delay(restLen);
  } else {
    digitalWrite(ledPinRed, HIGH);
    delay(playLen);
    digitalWrite(ledPinRed, LOW);
    delay(restLen);
  }
  delay(beatDuration - flashLen);
}
void countBeats() {
  //keeps the bpmCount from going over.
  bpmCount = bpmCount % bpmBottom;
  
  flashLed(bpmCount);
  //flashNote( getNoteDuration( bpmSequence[bpmCount], bpm ), bpmFlashNotes[bpmCount] );
  bpmCount ++;
}

void playMelody() {
 //calculate note_duration
 int noteDuration = 0;
 int notePitch = 0;
 
 //Steps through all the notes in the melody
 melodyCount = melodyCount % melodyLen;
 
 Serial.println("playing Note at i = " + String(melodyCount));
 Serial.println(noteLens[melodyCount]);
 noteDuration = getNoteDuration( noteLens[melodyCount], bpm);
 notePitch = notePitches[melodyCount];
 playNote(noteDuration, notePitch);
 melodyCount ++;
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

void loop() {
  
  playMelody();
  //countBeats();
  //delay(10000);
  
  but1Val = digitalRead(but1);
  pot1Val = analogRead(pot1);
  pot2Val = analogRead(pot2);
  
  //pot1Val = map( pot1Val , 0, 1023, 0, 127);
  
  if ( (millis() - timer) > timeDelay) {
    if(bpmTravelDirection == 1) {
      bpm ++;
    } else {
      bpm --;
    }
    if (abs(bpmTravelCount) > bpmTravelLimit) {
      bpmTravelDirection *= -1;
    }
    timer = millis();
  }
  
}
