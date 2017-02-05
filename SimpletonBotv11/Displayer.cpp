#include "Displayer.h"
#include <Arduino.h>

Displayer::Displayer(LiquidCrystal *lcd, int x, int y, int len) {
  this->lcd = lcd;
  this->x = x;
  this->y = y;
  this->dispLen = len;
  duration = 10000;
  text = &nullText;
  timer = millis(); // important! yikes
  state = DSTATE_IDLE;
  
  
  mode = DMODE_SCROLL;
  //substring positions
  pos_s = 0;
  pos_f = 0;
  strLen = 0;
  dispPos = 0;
  scrollStep = 0;
  stepDelay = 200;
  
  
};
Displayer::~Displayer() {
  
}

void Displayer::draw() {
    lcd->setCursor(x,y);
    lcd->print(*text);
};

void Displayer::clr() {
  lcd->setCursor(x,y);
  //print a bunch of spaces to clear old draw
  for( int i = 0; i < dispLen ; i ++ ) {
    lcd->print(" ");
  }
};

void Displayer::drawScrolling() {
  lcd->setCursor(dispPos,y);
  
  String portion = text->substring(pos_s,pos_f);
  
  Serial.print("pos_s : ");
  Serial.println(pos_s);
  Serial.print("pos_f: ");
  Serial.println(pos_f);
  Serial.println(portion);
  Serial.println("dispPos: " + String(dispPos));
  
  //lcd->print(scrollStep);
  lcd->print(portion);

  
};

void Displayer::update() {
  
  switch(state) {
    
    case DSTATE_DRAW:
      draw();
      state = DSTATE_WAITTOCLEAR;
      break;
      
    case DSTATE_WAITTOCLEAR:
      if ( (millis() - timer ) > duration ) {
        clr();
        state = DSTATE_IDLE;
      }
      break;
      
    case DSTATE_IDLE:
      //do nothing
      break;
      
    case DSTATE_DRAWSCROLLING:
      if ( ( millis() - timer ) > stepDelay ) {
        if (scrollStep <= strLen  ) {
          //Serial.print("strLen");
          //Serial.println(strLen);
          if( scrollStep > dispLen ) {
            pos_s = scrollStep - dispLen;
            Serial.println("thiiis ?? ");
          }
          
          
          //pos_f = pos_s + dispLen;
          
            
          
          if (dispPos > x ) {
            dispPos = x + dispLen - scrollStep; // maybe - 1 too
            
            pos_f = scrollStep; // draw only few chars
          } else {
            
            pos_f = pos_s + dispLen;
            // once dispPos is all the way 
            //left then draw full size
          }
            
          scrollStep += 1;
          
          //***********************
          drawScrolling();
          
        } else {
          //Serial.print("DSTATE_WAITTOCLEAR");
          state = DSTATE_WAITTOCLEAR;
          timer = millis();
        }
      
        timer = millis();
        //Serial.print("scrollStep: ");
        //Serial.println(scrollStep);
      }// end timer
      break;
      
    default:
      
      break;
  }

};

void Displayer::newTextScrolling(String * text, int duration) {
  this->text = text;
  this->duration = duration;
  
  //set the timer & state
  timer = millis();
  state = DSTATE_DRAWSCROLLING;
  
  //scrolling setup
  strLen = text->length();
  scrollStep = 0;
  //set disPos to right edge of Displayer
  dispPos = x + dispLen;
  pos_s = 0;
 
};




void Displayer::newText(String * text, int duration) {
  
  this->text = text;
  this->duration = duration;
  
  //set the timer & state
  timer = millis();
  state = DSTATE_DRAW;
};
  
  
