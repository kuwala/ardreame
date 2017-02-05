#ifndef ENTITY_H
#define ENTITY_H
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sprites.h"

  
#define TWO_PI 6.28
#define THREE_TWO_PI 4.712
#define HALF_PI 1.571
#define PI 3.14

class Entity {
  public:
    int startX;
    int startY;
    int x;
    int y;
    float angle;
    float motion;
    //float motionY;
    float r;
  Entity(int _x, int _y);
  void update();
  void draw(Adafruit_SSD1306 &disp);
};

#endif

