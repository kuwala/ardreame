#include <Arduino.h>
#include <Encoder.h>
#include <LiquidCrystal.h>

int piezoPin = 11;
int buttonsPin = A0;
int uvPin = 12;

// button input as resistor ladder
int buttonsValue = 0;
int buttonsState = 0; // state 1-4 for buttons

Encoder knob1(20, 24);
Encoder knob2(22, 21);



// knob values;
int left = 0;
int right = 0;

int rootNote = 0;
// sets the notes to start on c3
int noteOffset = -9; 

int thirdOffset = 4;
int fithOffset = 7;

int playState = 0;
int playNote = 0;

int curSeqNote = 0;
const int noteSeqLen = 16;
int noteSeq[noteSeqLen] = { 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1, 0};
int seqInsertPos = 0;
int noteDelay = 50;
int notePlaying = 0;

LiquidCrystal lcd(8, 7, 5, 4, 3, 2);



unsigned long timer = 0;
unsigned long playTimer = 0;
int timeDelay = 100;




void setup() {
  Serial.begin(9600);
  Serial.println(" d a n n y  <3 ");
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("A D M O - S Y N T H ");
  lcd.setCursor(0,1);
  lcd.print(" d a n n y  <3 ");
  tone(piezoPin, 44);
  delay(125);
  noTone(piezoPin);
  delay(250);
  lcd.clear();
  pinMode(uvPin, OUTPUT);
  digitalWrite(uvPin, HIGH);
}

int notePitchCalc(int n) {
  //n in halfsteps above A4;
  
  //fn freq in hz
  //fn = f0 * (a)^n 
  //f0 = 440hz // which is A4 above middle C
  //a = (2)1/12 = 1.059463094359
  float a = 1.059463094359;
  return 440 * pow(a, n);  
}

void getButtonInput() {
  buttonsValue = analogRead(buttonsPin);
  if(buttonsValue == 1023) {
    buttonsState = 1;
  }
  else if (buttonsValue >= 990 && buttonsValue <= 1010) {
    buttonsState = 2;
  }
  else if (buttonsValue >= 505 && buttonsValue <= 515) {
    buttonsState = 3;
  }
  else if (buttonsValue >= 5 && buttonsValue <= 10) {
    buttonsState = 4;
  }
  else {
    buttonsState = 0;
  }
  //Serial.println(buttonsValue);
}

int getSeqNote(int pos){
  if( pos < 0 ) {
    pos = noteSeqLen;     // ***** BUG in here curSeqNote should be Pos???
  } else if( curSeqNote > noteSeqLen - 1) {
    curSeqNote = 0;
  }
 return noteSeq[pos];
  
}
void setSeqNote(int pos, int note) {
  noteSeq[pos] = note;
}
void printSeq() {
   lcd.setCursor(0,0);
   for (int i = 0; i < noteSeqLen; i ++ ) {
    lcd.setCursor(i,0);
    lcd.print(getSeqNote(i));
   }
  lcd.setCursor(seqInsertPos,0);
  lcd.print("_");

}
int setSeqPos(int val) {
  if (val <0 ) {
    val = noteSeqLen - 1;
    knob1.write((noteSeqLen - 1) * 4);
    left = noteSeqLen - 1;
  } else if (val > noteSeqLen - 1) {
    val = 0;
    knob1.write(0);
    left = 0;
  }
  return val;
  
}

void loop() {
  getButtonInput();
  
  if (buttonsState == 1) {
        //insert note
        setSeqNote(seqInsertPos, rootNote);
        
      }
  
  
  right = knob2.read()  / 4;
  left = knob1.read() / 4;
  
  rootNote = right + noteOffset;
  
  seqInsertPos = setSeqPos(left);
  //Serial.println(left);
  //Serial.println(seqInsertPos);
  playNote = getSeqNote(curSeqNote);
  
  if( playState == 1 && notePlaying) {
    int pitch = notePitchCalc(playNote);
    tone(piezoPin,  pitch);
    
    
  } else {
    noTone(piezoPin);
    
  }
  if((millis() - playTimer) > noteDelay) {
      //toggle note on / off
     if( notePlaying == 0) {
       notePlaying = 1;
       //increase sequancer step
       curSeqNote++;
     } else {
       notePlaying = 0;
     }
     
     playTimer = millis();
  }
  
  
  
  if ((millis() - timer) > timeDelay ) {
    
    if(buttonsState == 3) {
    if(playState == 0) {
      playState= 1;
    } else {
      playState = 0;
    }
  } // end button
    
    lcd.clear();
    printSeq();
    
    
    lcd.setCursor(0,1);
    lcd.print("c ");
    if(playState==1) {
      lcd.print( noteSeq[curSeqNote] );
    } else {
      lcd.print( noteSeq[seqInsertPos] );
      
    }
    lcd.setCursor(6,1);
    lcd.print(rootNote);
    lcd.print(" ");
    lcd.print(rootNote + thirdOffset);
    lcd.print(" ");
    lcd.print(rootNote + fithOffset);
    lcd.print(" ");
    
    lcd.setCursor(15,1);
    if(playState==1) {
      lcd.print(">");
      lcd.setCursor(curSeqNote, 0);
      lcd.print(">");
      digitalWrite(uvPin, HIGH);
    } else {
      lcd.print("x");
      digitalWrite(uvPin, LOW);
    }
    
    timer = millis();
    
  }
 
  
  
} // end void loop()
