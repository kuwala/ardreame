#include "BBoy.h"
#include <LiquidCrystal.h>

BBoy::BBoy(){
  xp = 0; // experience ex: 10 bits
  hp = 0; // hunger points 00 / 10
  timer = 0;
  timeDelay = 50; // every 50 millis do a tick
  hpmax = 6;
  
};
void BBoy::xpGet(int _xp){
  xp += _xp;
  
}

BBoy::~BBoy(){
  
};

void BBoy::update(){
  
  if( ( millis() - timer ) > timeDelay ) {
    //getHungry();
    
    // Im hungry
    hp -- ;
    timer = millis();
  }
  
};

void BBoy::drawFace(LiquidCrystal *lcd){
  
  lcd->setCursor(posx,posy);
  lcd->print("  (");
  //lcd.write(B10100101); //circular eye dot
  // drawys dot eye;
  lcd->write((byte)0);
  lcd->print(" ");
  lcd->write(2); // "_" closed mouth
  lcd->print(" ");
  lcd->write((byte)0);
  lcd->print(")");
  
};
