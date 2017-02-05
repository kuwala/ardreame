/*
  Melody
 
 Plays a melody 
 
 circuit:
 * 8-ohm speaker on digital pin 8
 
 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe 

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone
 
 */




int const numPins = 7; // number of led pins used for lights
int ledPins[numPins] = { 2, 3, 4, 5, 6, 7, 8 };

int const rgbNumPins = 3;// Number of PWM pins
int rgbPins[rgbNumPins] = { 9, 10, 11 };
// The Possition of each colors PWM 
// 255 is low 0 is high. 

int long ledTimer = 0;
boolean ledsOn = false;
int ledTimeMax = 13;
int timeMaxRate = 0;
int timeMaxMax = 150;
int timeMaxMin = 1;
int rPos = 255, gPos = 255, bPos = 255;

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_E4, 
  NOTE_E4, NOTE_G4, NOTE_C3, NOTE_D3, 
  NOTE_E4,
  NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,
  NOTE_F4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_D3,NOTE_D4,NOTE_E4,
  NOTE_D3,NOTE_G4
  };

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int const  numNotes = 24; 
int noteDurations[numNotes] = {
  4,4,2, 
  4,4,2,
  4,4,4,4,
  1,
  4,4,4,4,
  4,4,2,
  4,4,4,4,
  2,2};

void setup() {
  
  Serial.begin(9600);
  
  for(int i = 0; i < numPins; i ++) {
    pinMode(ledPins[i], OUTPUT);
  }
  for(int i =0; i < rgbNumPins; i ++) {
    pinMode(rgbPins[i], OUTPUT);
  }
 
  // iterate over the notes of the melody:
  /*
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(12, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    
    for (int i = 0; i < numPins; i ++) {
      digitalWrite(ledPins[i], HIGH);
 
    }
    
    delay(noteDuration);
    
    for (int i = 0; i < numPins; i ++) {
      digitalWrite(ledPins[i], LOW);
    }
 
    int pauseBetweenNotes = noteDuration * 0.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(12);
    
  }
  */
  // Set Led Pins to output 
  
  

}


void loop() {
  // no need to repeat the melody.
  
  if (ledsOn == false && ( millis() - ledTimer > ledTimeMax ) ) {
    ledTimer = millis(); // set the timer
    ledTimeMax += timeMaxRate;
    
    Serial.print("ledTimeMax: ");
    Serial.print(ledTimeMax);
    Serial.print(", timeMaxMax: ");
    Serial.print(timeMaxMax);
    Serial.print('\n');   
    
    for (int i = 0; i < numPins; i ++) {
      digitalWrite(ledPins[i], HIGH);
    }
    if (ledTimeMax > timeMaxMax) {
      ledTimeMax = timeMaxMin;
    }
    ledsOn = true;
  }
  else if (millis() - ledTimer > ledTimeMax)
  {
    ledTimer = millis(); // set the timer
    
    for (int i = 0; i < numPins; i ++) {
      digitalWrite(ledPins[i], LOW);
    }
    ledsOn = false;
  }
 
}
