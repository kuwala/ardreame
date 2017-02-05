#include "Entity.h"
#include "Arduino.h"




Entity::Entity(int _x, int _y) {
  startX = _x - 11; // width?
  startY = _y - 10; // height?
  x = 0;
  y = _y;
  angle = 0;
  r = 63 - 11;
  motion = 0;
}
void Entity::update() {
  motion = ( r * sin(angle));
  //motionY = ( r * cos(angle));
  
  x = round(startX + motion);
  //y = round(startY + motionY);
  //debugging info
  Serial.print("Motion: ");
  Serial.println(motion);
  Serial.print("X: ");
  Serial.println(x);
  Serial.print("Angle: ");
  Serial.println(angle);
  
  //incriment angle
  angle = angle + 0.1;
  if( angle > TWO_PI) {
    angle = angle - TWO_PI;
  }
}
void Entity::draw(Adafruit_SSD1306 &disp) {
  
  //display.drawPixel(x,y, WHITE);
  
  //laser
  //display.drawLine(34,16,x,56, WHITE);
  if ( angle >= HALF_PI && angle <= THREE_TWO_PI) {
    disp.drawBitmap(x, y, duckyLeft_bmp, DUCK_W, DUCK_H, WHITE );
  } else {
    disp.drawBitmap(x, y, duckyRight_bmp, DUCK_W, DUCK_H, WHITE );
  }
  
   
}

