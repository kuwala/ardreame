/* * * * * * * * * * * * * * * * * * * *
 *   PD OSC to Display Interface      
 *   by Daniel
 * * * * * * * * * * * * * * * * * * * */

#include <OSCMessage.h>


#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
  SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
  SLIPEncodedSerial SLIPSerial(Serial);
#endif

/* * * * * * * * * * * * * * * * * * * *
 *         Display   Includes
 * * * * * * * * * * * * * * * * * * * */
#ifndef DISP_INC_H
#define DISP_INC_H
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#endif

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
//128x64 pixels


//Pin Defines
int knob = A0;


// Send OSC Timer
unsigned long timer = 0;
int maxWait = 20; //20 millis



void splashScreen() {
  display.clearDisplay();
  display.setCursor(16, 12);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print("Dnny-OS");
  display.display();
  delay(500);
}

void setup() {
  //Begin Serial
  SLIPSerial.begin(9600); // baud Rate affects proformance
  //Display Setup
  //Initialized with I2C addr 0x3C or 0x3D
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  //Splash Intro With Delay(500);
  splashScreen();
  
}

void updateDisplay(OSCMessage &msg)
{
  display.clearDisplay();
  display.setCursor(16,12);
  if (msg.isString(0)) {
    int length = msg.getDataLength(0);
    char str[length];
    msg.getString(0,str,length);
    display.print(str);
  }
  if (msg.isInt(0) ) {
    int num = msg.getInt(0);
    display.print(num);
  }
  display.display();
  
}

void loop() {
  
  //* * * * * * * * * * * * * * * * * * * * * * *
  //Recieve OSC
  //* * * * * * * * * * * * * * * * * * * * * * *
  OSCMessage msgIN;
  int size;
  while(!SLIPSerial.endofPacket()) {
    if ( (size=SLIPSerial.available()) > 0) { 
      while(size--)
        msgIN.fill(SLIPSerial.read());
    }
  }
  
  if (SLIPSerial.available())
  
  //* * * * * * * * * * * * * * * * * * * * * * *
  //Send OSC
  //* * * * * * * * * * * * * * * * * * * * * * *
  
  /*
  if ( ( millis() - timer ) > maxWait ) {
    OSCMessage msgOUT("/a/0"); //analog pin 0
    msgOUT.add((int32_t)analogRead(knob));
    SLIPSerial.beginPacket();
    msgOUT.send(SLIPSerial);
    SLIPSerial.endPacket();
    msgOUT.empty();
    
    timer = millis();
  } */
 

  //Dispatch messages
  if(!msgIN.hasError())
    msgIN.dispatch("/disp" , updateDisplay);
}
