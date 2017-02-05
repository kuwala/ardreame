#include "Displayer.h"
#include <Arduino.h>

Displayer::Displayer(LiquidCrystal *lcd, int x, int y, int len) {
  this->lcd = lcd;
  this->x = x;
  this->y = y;
  this->len = len;
  duration = 10000;
  text = &nullText;
  timer = millis(); // important! yikes
  state = true;
  
};
Displayer::~Displayer() {
  
}

void Displayer::draw() {
  
  lcd->setCursor(x,y);
  lcd->print(*text);
  //lcd->print("I work !");
  //Serial.println(" : ( " );
  
  
};

void Displayer::clr() {
  Serial.println("O M G    CLEARING");
  lcd->setCursor(x,y);
  //print a bunch of spaces to clear old draw
  for( int i = 0; i < len ; i ++ ) {
    lcd->print(" ");
  }
};

void Displayer::update() {
  
  //check state
 
  if(state == true) {
     //Serial.println("work?");
   if ( (millis() - timer ) < duration ) {
     draw();
      //Serial.println("please");
     
   } else {
     state = false;
     clr();
   }
    
  } else {
    //Serial.println("We not doing notthing");
    // do nothing
  }
  
};


void Displayer::newText(String * text, int duration) {
  
  this->text = text;
  this->duration = duration;
  
  //set the timer & state
  timer = millis();
  state = true;
};
  
  
