#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Entity.h"


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
//128x64 size display


Entity danny(63,40);
Entity sarah(44, 56);

void setup() {
  Serial.begin(9600);
  
  //Initialize with I2C addr 0x3D
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //display.fillCircle(24, 24, 16, WHITE);
  //display.drawPixel(42,40, WHITE);
  //display.drawPixel(42,42, WHITE);
}

void surprise () {
 display.setCursor( 16, 12 );
 display.setTextColor(WHITE);
 display.setTextSize(2);
 display.print("Hi Sammy");
 
  
}

int counter = 0;
void loop() {
    display.clearDisplay();
    display.drawLine(0,34,127,34,WHITE);
    danny.draw(display);
    
    if(counter >9 ) {
      surprise();
    }
    
    display.display();
    delay(10);
    danny.update();
    counter ++;
    counter = counter % 19;
    
}
