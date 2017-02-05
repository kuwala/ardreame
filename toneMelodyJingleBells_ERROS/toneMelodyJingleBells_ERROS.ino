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
int rgbPins[rgbNumPins] = { 11, 10, 9 };
// The Possition of each colors PWM 
// 255 is low 0 is high. 
//LED intensities
int redLedInt = 0;
int bluLedInt = 0;
int grnLedInt = 0;

int long ledTimer = 0;
boolean ledsOn = false;
int ledTimeMax = 10;
int timeMaxRate = 1;
int timeMaxMax = 1000;
int timeMaxMin = 10;
int rPos = 255, gPos = 255, bPos = 255;

#include "pitches.h"

// notes in the melody:
int const REST = 0;
int const randMelodyLen = 8;
int randMelody[randMelodyLen];
int randMelodyDur[randMelodyLen];

// 5 notes and 1 root octave higher
int scaleCMajPent[6] = {
  NOTE_C4, NOTE_D4, NOTE_E4, 
  NOTE_G5, NOTE_A4, NOTE_C5
};

int const durationLen = 4;
int durations[durationLen] = {
  1, 2, 4, 8
};

int const durationLen2 = 4;
int durations2[durationLen2] = {
  8,8,16,4
};


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
  
  // Sets the rgbLED  to low
  for(int i =0; i < rgbNumPins; i ++) {
    analogWrite(rgbPins[i], HIGH);
  }
  
  pinMode(butPin, INPUT);
 
  
  
  // Set Led Pins to output 
  
  

}

void randomizeMelody() {
  int  setDurationLen;
  int* setDurations ;
  if (random(0,2)) {
    setDurationLen = durationLen2;
    setDurations = durations2;
  } else {
    setDurationLen = durationLen;
    setDurations = durations;
  }
    
  for (int i=0; i <randMelodyLen; i ++) {
    randMelody[i] = scaleCMajPent[random(6)];
    randMelodyDur[i] = setDurations[random(setDurationLen)];
  }
}
void playRandMelody() {
  
  for (int thisNote= 0; thisNote < randMelodyLen; thisNote++) {
    
    int noteDuration = 1000/randMelodyDur[thisNote];
    tone(12, randMelody[thisNote], noteDuration);
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

void playJingleBells() {
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

void pwmRampUp(int pin, int cStep) {
  if (cStep < 256) {
    analogWrite(pin, 255 - cStep);
    // 255 - cStep because we need to invert the value
    // because the rgb LED is comman Anode
  }
}

void redLedPwm(int cStep) {
  digitalWrite(rgbPins[1], HIGH);
  digitalWrite(rgbPins[2], HIGH);
  
  // first block ramp up, second & third block stay bright, then 4th ramp down, then 5th & 6th stay dim.
  // each block is 0 - 255 ( 256) values; 
  
  if (cStep < 256) {
    analogWrite(rgbPins[0], 255 - cStep);
    // 255 - cStep because we need to invert the value
    // because the rgb LED is comman Anode so 0 is brightest 255 is dimist.
    redLedInt = 255 - cStep;
    Serial.print("1st \n");
  }
  else if (cStep > 255 && cStep < 768) { // 2nd and 3rd block
    redLedInt = 0; // brightest
    Serial.print("2dn adn 3rd \n");
  }
  else if (cStep > 767 && cStep < 1024) { // 4th block
    //ramp down
    redLedInt =  768 - (cStep + 256);
    Serial.print("4th \n");
  }
  else if (cStep > 1023) { // 5th and 6th , and the rest of the blocks are set to dimist
    redLedInt = 255;
    Serial.print("last Blocks\n");
  }
  
  analogWrite(rgbPins[0], redLedInt);
  //Serial.print(cStep);
  //Serial.print("\n");
  
}

void redLedRand(int cStep) {
  analogWrite(rgbPins[0], random(255));
}
void grnLedRand(int cStep) {
  analogWrite(rgbPins[1], random(255));
}
void bluLedRand(int cStep) {
  analogWrite(rgbPins[2], random(255));
}
  

int const numScenes = 3;
int curScene = 1;
// scene[0] = sceneRandLed ; scene[1] = sceneSeriesLed ; sceneBlinkLeds ;
int sceneSteps[numScenes] = { 10, 14, 6 }; // number of steps + 1;cuz steps start at 0
int sceneStepInterval[numScenes] = { 1000, 200, 500 }; // in mill secs
boolean timerOn = false;
int sceneStep = 0; // starts at 0 and goes to ( scemeSteps[curScene] - 1 )
int long sceneTimer;

int melodyBut = 0;

int const rgbNumScenes = 2;
int rgbCurScene = 0;
int rgbSceneSteps[rgbNumScenes] = { 1566, 20 };
int rgbSceneStepInterval[rgbNumScenes] = { 10, 200 };
boolean rgbTimerOn = false;
int rgbSceneStep = 0; 
int long rgbSceneTimer = 0;



void loop() {
  // no need to repeat the melody.
  
  
  //sets the timers counting
  if ( timerOn == false ) {
    sceneTimer = millis();
    timerOn = true;
  }
  
  if (rgbTimerOn == false) {
    //Serial.print("rgb timer reset");
    rgbSceneTimer = millis();
    rgbTimerOn = true;
  }
  
  
  
  //rgb scenes
  if ( ( millis() - rgbSceneTimer) > rgbSceneStepInterval[rgbCurScene])  {
    if (rgbSceneStep > rgbSceneSteps[rgbCurScene] ) {
      rgbSceneStep = 0;
      rgbCurScene ++; // change to next scene
    }
    if (rgbCurScene > (rgbNumScenes - 1) ) {
      rgbCurScene = 0;
    }
    switch(rgbCurScene) {
      case 0:
        redLedPwm(rgbSceneStep);
        //Serial.print(rgbSceneStep);
       // Serial.print("\n");
       // Serial.print(rgbSceneTimer);
        //Serial.print("\n");
        break;
        
      case 1:
        redLedRand(rgbSceneStep);
        grnLedRand(rgbSceneStep);
        bluLedRand(rgbSceneStep);
      
       Serial.print("rgb not doing noting \n");
        break;
        
        
      default:
        break;
    }
    
    rgbSceneStep ++;
    rgbTimerOn = false;
    // read button for melody
  }
    
  
  // led scenes
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
        //playJingleBells();
        randomizeMelody();
        playRandMelody();
    }
    
    //Serial.print(melodyBut);
   // Serial.write("HELLOO");
    //Serial.write("\n");
    
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
