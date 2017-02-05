#include "BBoy.h"
//#include <LiquidCrystal.h>


BBoy::BBoy(){
  xp = 0; // experience ex: 10 bits
  hp = 2; // hunger points 00 / 10
  hpMax = 6;  
  timer = 0;
  timeDelay = 50; // every 50 millis do a tick
  nagDelay = 5000;
  nagTimer = 0;
  
  thoughtText = &nullTxt;

  state = BSTATE_IDLE;
  
  
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
  Serial.println(hp);
  
};


  

void BBoy::xpGet(int _xp){
  xp += _xp;
  
};

BBoy::~BBoy(){
  
};

void BBoy::update(){
 
  switch(state) {
  
    case BSTATE_IDLE:

      if( ( millis() - timer ) > timeDelay ) {
        Serial.println(millis());
        timer = millis();
        
        // Transition to hungry
        if ( hp < HUNGERLINE ) {
          thoughtText = & hungryTxt;
          disp->newText(thoughtText, MEDDELAY);
          state = BSTATE_HUNGRY;
          nagTimer = millis();
        }
  
      } // end timer
      
      if( ( millis() - nagTimer ) > nagDelay) {
        
        // not thoughtText
        disp->newText(&questionTxt, MEDDELAY);
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
     
   default:
  
      break;
  }//end of switch

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
