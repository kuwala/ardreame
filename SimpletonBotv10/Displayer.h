#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <Arduino.h>
#include <LiquidCrystal.h>

// nullText may need to be moved to global vars
String static nullText = " ";

class Displayer {
  private:
    int x, y, pos;
    int len;
    boolean state;
    int displaySize;
    
    unsigned long timer;
    unsigned long duration; // in millis to display
    
    LiquidCrystal* lcd;
    String* text;
    
  public:
    void draw();
    void clr(); // clear display area
    void newText(String * text, int duration); //set text and duraiton
    void update(); // checks state and timer then display
    Displayer(LiquidCrystal *lcd, int x, int y, int len); 
    ~Displayer();
};

#endif
