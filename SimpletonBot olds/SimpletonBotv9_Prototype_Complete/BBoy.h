#ifndef BBOY_H
#define BBOY_H
#include <Arduino.h>
#include <LiquidCrystal.h>

class BBoy {
  public:
    BBoy();
    ~BBoy();
    void update();
    void drawFace(LiquidCrystal* lcd);
    int xp;
    int hp;
    int hpmax;
    unsigned long timer;
    unsigned long timeDelay;
    void xpGet(int _xp);
    
    //Where to set Cursor to draw face
    static const int posx = 7;
    static const int posy = 1;
  
};

#endif
