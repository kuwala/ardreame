#include <Arduino.h>
#include <Encoder.h>
#include <LiquidCrystal.h>

int piezoPin = 11;
int buttonsPin = A0;
int uvPin = 12;

// button input as resistor ladder
int buttonsValue = 0;
int buttonsState = 0; // state 1-4 for buttons

Encoder knob1(22, 21);
Encoder knob2(24, 20);

// knob values;
int left = 0;
int right = 0;

LiquidCrystal lcd(8, 7, 5, 4, 3, 2);



unsigned long timer = 0;
int timeDelay = 44;




void setup() {
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
  //n is halfsteps above A4;
  
  //fn = f0 * (a)^n 
  //fo = 440hz // which is A4 above middle C
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

void loop() {
  getButtonInput();
  left = knob1.read()  / 4;
  right = knob2.read()  ;
  
  //timeDelay = knob2.read() / 4;
  if ((millis() - timer) > timeDelay ) {
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Delay Time: ");
    lcd.print(timeDelay);
    
    lcd.setCursor(0,1);
    
    lcd.print(left);
    lcd.print("     B: ");
    lcd.print(buttonsState);
    timer = millis();
    
  }
  if(buttonsState == 4) {
    knob1.write(0);
    
  }
  
}
