#ifndef BBOY_H
#define BBOY_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Displayer.h"

#define HUNGERLINE 3
#define MEDDELAY 500 // in millis
String static hungryTxt = "Im Hungy";
String static yumTxt = " Yum ";
String static fullTxt = "Im full!";
String static hiyaTxt = "Oh Hiya.";
String static allbetterTxt = "All Better";
String static thanksTxt = "Thaankss";
String static questionTxt = "  ..?..";
String static nullTxt = ""; // maybe should be /n?

enum BBoyState { //bs = boystate
  BSTATE_IDLE,
  BSTATE_UPDATING,
  BSTATE_SLEEPING,
  BSTATE_HUNGRY,
  BSTATE_TRAINING,
  BSTATE_PLAYING
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
    
    String * thoughtText;
    Displayer * disp;
    
    BBoyState state;
    
    
    void xpGet(int _xp);
    
    void feed(int value);
    
    
    
    //Where to set Cursor to draw face
    static const int posx = 7; // optimize to defines
    static const int posy = 1;
  
};

#endif
