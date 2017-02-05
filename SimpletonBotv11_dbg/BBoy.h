#ifndef BBOY_H
#define BBOY_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Displayer.h"
#include "AllTexts.h"

#define HUNGERLINE 3
#define MEDDELAY 500 // in millis


enum BBoyState { 
  BSTATE_IDLE,
  BSTATE_UPDATING,
  BSTATE_SLEEPING,
  BSTATE_HUNGRY,
  BSTATE_TRAINING,
  BSTATE_PLAYING,
  BSTATE_PAUSE // for pausing FSM
};
  


class BBoy {
  public:
    BBoy();
    ~BBoy();
    void update();
    void drawFace(LiquidCrystal* lcd);
    void setDisplayer(Displayer* disp);
    
    //stats
    int xp;
    int xpToNextLevel;
    int hp; //  all these stats 
    int hpMax; // need to be optimized as byte ?
    int power;
    int powerMax;
    int hearts;
    int heartsMax;
    
    unsigned long timer;
    unsigned long timeDelay;
    
    unsigned long nagTimer;
    int nagDelay; // display nag text after
    
    int pauseDelay;
    
    String * thoughtText;
    Displayer * disp;
    
    BBoyState state;
    BBoyState prevState;
    
    
    void xpGet(int _xp);
    
    void feed(int value);
    void pause(int _pauseDelay);
    void setThought(String * newThoughtText);
    
    
    
    
    
    //Where to set Cursor to draw face
    static const int posx = 7; // optimize to defines
    static const int posy = 1;
  
};

#endif
