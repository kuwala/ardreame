#include "BBoy.h"
//#include <LiquidCrystal.h>
#include <Arduino.h>

BBoy::BBoy(){
  xp = 0; // experience ex: 10 bits
  hp = 5; // hunger points 00 / 10
  hpMax = 10;  
  timer = 0;
  timeDelay = 50; // every 50 millis do a tick
  nagDelay = 5000;
  nagTimer = 0;
  pauseDelay = 5500;
  
  
  thoughtText = &nullTxt;

  state = BSTATE_IDLE;
  prevState = BSTATE_IDLE;
  
  
};


void BBoy::feed(int value){
  if (hp < hpMax) {
    hp += value;
    //thoughtText = &yumTxt;
    disp->newText(&yumTxt, MEDDELAY);
    // say yum
  }
  if (hp >= hpMax ) {
    hp = hpMax;
    //thoughtText = &fullTxt;
    disp->newText(&fullTxt, MEDDELAY);
    // say I am full
    
  }
  //Serial.println(hp);
  
};


  

void BBoy::xpGet(int _xp){
  xp += _xp;
  
};

BBoy::~BBoy(){
  
};
void BBoy::setThought(String *newThoughtText) {
  thoughtText = newThoughtText;
}

void BBoy::update(){
 
  switch(state) {
  
    case BSTATE_IDLE:

      if( ( millis() - timer ) > timeDelay ) {
        Serial.println(millis());
        timer = millis();
        
        // Transition to hungry
        if ( hp < HUNGERLINE ) {
          thoughtText = & hungryTxt;
          
          //thoughtText = & veryLongTxt;
          disp->newTextScrolling(thoughtText, MEDDELAY);
          state = BSTATE_HUNGRY;
          nagTimer = millis();
        }
  
      } // end timer
      
      if( ( millis() - nagTimer ) > nagDelay) {
        
        // not thoughtText
        disp->newTextScrolling(&questionTxt, MEDDELAY);
        nagTimer = millis();
        
      }
      
     
      break;
    
    case BSTATE_HUNGRY:
      if( ( millis() - nagTimer ) > nagDelay) {
        disp->newText(thoughtText, MEDDELAY);
        nagTimer = millis();
        
      } else if ( ( millis() - timer ) > timeDelay ) {
        timer = millis();
        if ( hp > HUNGERLINE ) {
          thoughtText = &hiyaTxt;
          //diff then thought
          disp->newText(&thanksTxt, MEDDELAY);
          state = BSTATE_IDLE;
          nagTimer = millis();
          
        };
      }
    
      break;
      
    case BSTATE_SLEEPING:
   
      break;
      
    case BSTATE_PAUSE:
      if ( ( millis() - timer ) > pauseDelay) {
        state = prevState; 
      }
     
   default:
  
      break;
  }//end of  STATE switch
  

};

void BBoy::pause(int _pauseDelay) {
  pauseDelay = _pauseDelay;
  prevState = state;
  state = BSTATE_PAUSE;
};

void BBoy::setDisplayer(Displayer* disp) {
  this->disp = disp;
  
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
