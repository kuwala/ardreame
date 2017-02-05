#ifndef SPINNYSYNTH_H
#define SPINNYSYNTH_H

#include <Arduino.h>
#include <Encoder.h>
#include "DisplayVars.h"

// Change these pin numbers to the pins connected to your encoder. 
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

//21, 20 interupt pins
//22, 24 normal pins

Encoder knob(21, 22);
Encoder knob2(20, 24);

int pitchStep = 0;
int knobDivits = 20;

int buttonState = 0;
int button2State = 0;

int rootNote = -9;
int rootNote2 = 3;
int butInterval = 5;

int pentScaleRes[] = { 2, 4, 7, 9, 12};
int pentScale[] = { 2, 2, 3, 2, 3 };
//int pentScale[] = { 2, 2, 3, 2, 3, 2, 2, 3, 2, 3, 2, 2, 3, 2, 3, 2, 2, 3, 2, 3 };
int knobPos = 0;

int butPin = 4;
int but2Pin = 5;
int piezoPin = 8;
int rLed = 10;
int bLed = 11;
int yLed = 6;
int rLedPwm = 0;
int bLedPwm = 0;


unsigned int long timer = 0;
int delayTime = 400;

int gateOn = 0;
int playNote = 0;
int const gateNumSteps = 11;
int delays[gateNumSteps] = { 800, 400, 200, 100, 50, 25, 13, 7, 4, 2, 1};
int knob2Pos = 0;
int gateStep = 0;


void spinnySetup() { 
  
  
  //Serial.begin(9600);
  Serial.println("@kuwala");
  Serial.println("@ @ @ Spinning~Around @ @ @");
  pinMode(piezoPin, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  pinMode(yLed, OUTPUT);
  pinMode(butPin, INPUT); // button
}
int spinnyNotePitchCalc(int n) {
  //n is halfsteps above A4;
  
  //fn = f0 * (a)^n 
  //fo = 440hz // which is A4 above middle C
  //a = (2)1/12 = 1.059463094359
  float a = 1.059463094359;
  return 440 * pow(a, n);  
}

void spinnyLoop () {
  
 rLedPwm = pitchStep % knobDivits;
 rLedPwm = map(rLedPwm, -20, 20, 0 , 255);
 
 pitchStep = (knob.read() / 4) ;
 gateStep = (knob2.read() / 4);
 
 buttonState = digitalRead(butPin);
 button2State = digitalRead(but2Pin);
 

 
 if( gateStep > 0.) {
   gateOn = 1;
   gateStep = gateStep % gateNumSteps;
   delayTime = delays[gateStep];
 } else {
   gateOn = 0;
 }
 
 if( gateOn == 1 ) {
 
   if ((millis() - timer) > delayTime) {
     
     //Toggle Note
      if (playNote == 0) {
        playNote = 1;
      } else {
        playNote = 0;
      } 
      
      timer = millis();
     
   }
   if ( playNote ) {
       tone(piezoPin,  spinnyNotePitchCalc(pitchStep));
       //tone(piezoPin, spinnyNotePitchCalc(pitchStep + (buttonState * 4) + (button2State * 7)));
       Serial.println("Spinny Note pitch calc " + String( spinnyNotePitchCalc(pitchStep + (buttonState * 4) + (button2State * 7)) ) );
       tone(piezoPin, 120);
       //digitalWrite(bLed, HIGH);
      // digitalWrite(yLed, LOW);
     
   } else {
       noTone(piezoPin);
       //digitalWrite(bLed, LOW);
       //digitalWrite(yLed, HIGH);
   
   }
   if (buttonState || button2State) {
     //digitalWrite(rLed, HIGH);
   } else {
     //digitalWrite(rLed, LOW);
   };
   
 } else {
  tone(piezoPin,  spinnyNotePitchCalc(pitchStep));
 
 }; 
}

#endif
