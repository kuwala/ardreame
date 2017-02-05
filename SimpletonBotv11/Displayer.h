#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <Arduino.h>
#include <LiquidCrystal.h>

//differnt kids of displays
enum dispMode {
  DMODE_SCROLL,
  DMODE_FLASH
};

enum DisplayerState {
  DSTATE_DRAW,
  DSTATE_DRAWSCROLLING,
  DSTATE_WAITTOCLEAR,
  DSTATE_IDLE // wait for new text
};

// nullText may need to be moved to global vars
String static nullText = " ";

class Displayer {
  private:
    int x, y;
    int dispLen; 
    
    DisplayerState state;
    dispMode mode;
    
    int strLen;
    int pos_s, pos_f;
    int dispPos;
    int scrollStep; // 0 - strLen (? + dispLen)
    int stepDelay; // used with timer
    
    unsigned long timer;
    unsigned long duration; // in millis to display
    
    LiquidCrystal* lcd;
    String* text;
    
  public:
    void draw();
    void drawScrolling();
    void clr(); // clear display area
    void newText(String * text, int duration); //set text and duraiton
    void newTextScrolling(String * text, int duration);
    void update(); // checks state and timer then display
    Displayer(LiquidCrystal *lcd, int x, int y, int len); 
    ~Displayer();
};

#endif
