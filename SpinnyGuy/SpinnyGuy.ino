#include <Encoder.h>
// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

//Encoder knob(3, 2);
Encoder knob(2, A2);
Encoder knob2(3, A1);

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


void setup() { 
  
  Serial.begin(9600);
  Serial.println("@kuwala");
  
  pinMode(piezoPin, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  pinMode(yLed, OUTPUT);
  pinMode(butPin, INPUT); // button
}
int notePitchCalc(int n) {
  //n is halfsteps above A4;
  
  //fn = f0 * (a)^n 
  //fo = 440hz // which is A4 above middle C
  //a = (2)1/12 = 1.059463094359
  float a = 1.059463094359;
  return 440 * pow(a, n);  
}


void loop () {
  
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
       tone(piezoPin, notePitchCalc(pitchStep + (buttonState * 4) + (button2State * 7)));
       digitalWrite(bLed, HIGH);
       digitalWrite(yLed, LOW);
     
   } else {
       noTone(piezoPin);
       digitalWrite(bLed, LOW);
       digitalWrite(yLed, HIGH);
   
   }
   if (buttonState || button2State) {
     digitalWrite(rLed, HIGH);
   } else {
     digitalWrite(rLed, LOW);
   };
   
 } else { // gate mode off so play sound with buttons
   
    if (buttonState == HIGH ) {
       tone(piezoPin, notePitchCalc(pitchStep));
       digitalWrite(bLed, HIGH);
       digitalWrite(yLed, LOW);
       //digitalWrite(rLed, LOW);
       
     } else if (button2State == HIGH) {
       int addOn = pentScaleRes[random(0,5)];
       tone(piezoPin, notePitchCalc(pitchStep + butInterval));
       digitalWrite(rLed, HIGH);
       digitalWrite(yLed, LOW);
     
    
    
    
    } else {
       noTone(piezoPin);
       digitalWrite(bLed, LOW);
       digitalWrite(rLed, LOW);
       digitalWrite(yLed, HIGH);
       
     }
 
 }
   
 
 
 
 
 
 
 //analogWrite(rLed, rLedPwm);
 
 /*
 for( int i = -20; i < 20; i ++ ) {
  tone(8, notePitchCalc(i)); 
  delay(100 + i*2);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  noTone(8);
  delay(100 + i*2);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
 } */
  
}

