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



int butPin = 13;
int const numPins = 7; // number of led pins used for lights
//int ledPins[numPins] = {  6, 7,  8, 4, 2, 5, 3 }; led order from bottom to top with ' S ' shape
int ledPins[numPins] = {  6, 7,  8, 4, 2, 5, 3 };
int const rgbNumPins = 3;
int rgbPins[rgbNumPins] = { 9, 10, 11 };
// The Possition of each colors PWM 
// 255 is low 0 is high. 

int long ledTimer = 0;
boolean ledsOn = false;
int ledTimeMax = 10;
int timeMaxRate = 1;
int timeMaxMax = 1000;
int timeMaxMin = 10;
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
  
  pinMode(butPin, INPUT);
 
  
  
  // Set Led Pins to output 
  
  

}

void playMelody() {
  // iterate over the notes of the melody:
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
}

void sceneRandLed(int cStep) {
  
  // set all 7 ledPins to a random on / off
  for(int i = 0; i < numPins; i++) {
    digitalWrite(ledPins[i], int( random(2) ));
  }

}

void sceneSeriesLed(int cStep) {
  switch(cStep) {
    case 0:
      // set all LEDS to low
      for(int i = 0; i < numPins; i++) {
        digitalWrite(ledPins[i], LOW);
      }
      break;
      
    case 1:
      digitalWrite(ledPins[0], HIGH);
      break;
    
    case 2:
      digitalWrite(ledPins[1], HIGH);
        break;
    
    case 3:
      digitalWrite(ledPins[2], HIGH);
        break;
    
    case 4:
      digitalWrite(ledPins[3], HIGH);
        break;
    
    case 5:
      digitalWrite(ledPins[4], HIGH);
        break;
      
    case 6:
      digitalWrite(ledPins[5], HIGH);
        break;
      
    case 7:
      digitalWrite(ledPins[6], HIGH);
        break;
        
    case 8:
      digitalWrite(ledPins[0], LOW);
      break;
    
    case 9:
      digitalWrite(ledPins[1], LOW);
        break;
    
    case 10:
      digitalWrite(ledPins[2], LOW);
        break;
    
    case 11:
      digitalWrite(ledPins[3], LOW);
        break;
    
    case 12:
      digitalWrite(ledPins[4], LOW);
        break;
      
    case 13:
      digitalWrite(ledPins[5], LOW);
        break;
      
    case 14:
      digitalWrite(ledPins[6], LOW);
        break;
    default :
       
        break;
  }
}

void sceneBlinkLeds( int cStep) {
  switch(cStep) {
    case 0:
      for(int i = 0; i < numPins; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
      
      break;
      
    case 1:
      for(int i = 0; i < numPins; i++) {
        digitalWrite(ledPins[i], LOW);
      }
    
      break;
      
    case 2:
      for(int i = 0; i < numPins; i++) {
          digitalWrite(ledPins[i], HIGH);
        }
    
      break;
      
    case 3:
      for(int i = 0; i < numPins; i++) {
          digitalWrite(ledPins[i], LOW);
        }
    
      break;
      
    case 4:
      for(int i = 0; i < numPins; i++) {
          digitalWrite(ledPins[i], HIGH);
        }
      break;
      
    case 5:
      for(int i = 0; i < numPins; i++) {
          digitalWrite(ledPins[i], LOW);
        }
      break;
    case 6:
      // extra delay
      break;
      
    default:
      break;
  }
  
} // end of sceneBlinkLeds()


int const numScenes = 3;
int curScene = 1;
// scene[0] = sceneRandLed ; scene[1] = sceneSeriesLed ; sceneBlinkLeds ;
int sceneSteps[numScenes] = { 10, 14, 6 }; // number of steps + 1;cuz steps start at 0
int sceneStepInterval[numScenes] = { 1000, 200, 200 }; // in mill secs
boolean timerOn = false;
int sceneStep = 0; // starts at 0 and goes to ( scemeSteps[curScene] - 1 )
int long sceneTimer;

int melodyBut = 0;

void loop() {
  // no need to repeat the melody.
  
  
  //sets the timer counting
  if ( timerOn == false ) {
    sceneTimer = millis();
    timerOn = true;
  }
  
  if ( (millis() - sceneTimer > sceneStepInterval[curScene]) ) {
    //sceneSeriesLed(sceneStep);
    if (sceneStep > sceneSteps[curScene] ) {
      sceneStep = 0;
      curScene ++; // change to the next scene
    }
    if (curScene > ( numScenes - 1 ) ) {
      curScene = 0;
    }
    
    switch(curScene) {
      case 0:
        sceneRandLed(sceneStep);
        break;
        
      case 1:
        sceneSeriesLed(sceneStep);
        break;
        
      case 2:
        sceneBlinkLeds(sceneStep);
        break;
        
      default:
        break;
    }
        
    
    sceneStep ++;
    timerOn = false;
    
    melodyBut = digitalRead(butPin);
    if (melodyBut == 1) {
        // iterate over the notes of the melody:
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
    }
    
    Serial.print(melodyBut);
    Serial.write("HELLOO");
    Serial.write("\n");
    
  }  
  
  
  /*
  if (ledsOn == false && ( millis() - ledTimer > ledTimeMax ) ) {
    ledTimer = millis(); // set the timer
    ledTimeMax += timeMaxRate;
    Serial.write("ledTimeMax: ");
    Serial.write(ledTimeMax);
    Serial.write(", timeMaxRate: ");
    Serial.write(timeMaxRate);
    Serial.write('\n');   
    for (int i = 0; i < numPins; i ++) {
      digitalWrite(ledPins[i], HIGH);
    }
  }
  else if (millis() - ledTimer > ledTimeMax)
  {
    ledTimer = millis(); // set the timer
    
    for (int i = 0; i < numPins; i ++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
  */
 
}
