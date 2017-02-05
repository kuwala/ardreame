#include "EventManager.h"



void EventManager::setBoyDisp(BBoy* _bBoy, Displayer* _disp){
  
  bBoy = _bBoy;
  disp = _disp;
  
};

void EventManager::update() {
  if (( millis() - eventTimer) > eventDelay) {
    randEvent();
    eventTimer = millis();
    bBoy->pause(5500);
  }
  
};


void EventManager::randEbook() {
  disp->newTextScrolling(&readEbookTxt, 500);
  
};

void EventManager::randEat() {
  disp->newTextScrolling(&eatFoodTxt, 500);
};
void EventManager::randLearned() {
  disp->newTextScrolling(&learnedTxt, 500);
  
};
void EventManager::randHurt() {
  disp->newTextScrolling(&hurtTxt, 500);
  
};

EventManager::EventManager() {
  
  eventTimer = 0;
  eventDelay = 12000;
  
  
  
};

void EventManager::randEvent() {
  int rand = random(numEvents);
  switch(rand) {
    case 0:
      randEbook();
    
      break;
    case 1:
      randEat();
      
      break;
    case 2:
      randLearned();
      
      break;
    case 3:
      randHurt();
      
      break;
    default:
      break;
  } // end switch
    
};


