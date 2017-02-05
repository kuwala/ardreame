/* * * * * * * * * * * * * * * * * * * *
 *   PD OSC to Display Interface      
 *   by Daniel, gfx by Sarah,
 *   Cars & Skulls by Sarah
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

#include "sprites.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
//128x64 pixels


//Pin Defines
int knob = A0;


// Send OSC Timer
unsigned long timer = 0;
int maxWait = 20; //20 millis

void initPrintText() {
  display.setTextColor(WHITE);
  display.setTextSize(1);
}

void drawLoading() {
  display.clearDisplay();
  display.drawBitmap(0,0, loading_bmp, LOADING_W, LOADING_H, WHITE ); 
  display.display();
}

void drawDrumSet() {
  display.clearDisplay();
  display.drawBitmap(0,0, drumset_proto, MAX_W, MAX_H, WHITE );
  display.display();
}

void drawDrumHit(int drum) {
  // drum range 0 - 7
  
  int yOffset = 3;// shift sprite 1 pixel down
  int xOffset;
  
  
  int drumNum = drum % 4;
  
  if (drum < 5) {
    //top row
    yOffset += 0 ;
  } else {
    //bottom row
    yOffset += 32 ;
  }
  
  xOffset =drumNum * 32;
  display.fillRect(xOffset,yOffset, DRUM_EACH_W, DRUM_EACH_H, BLACK);
  display.drawBitmap(xOffset,yOffset, drum_skull_hit, DRUM_EACH_W, DRUM_EACH_H, WHITE );
  display.display(); 
  
}

void drawDrums() {
  display.clearDisplay();
  display.drawBitmap(16,16, drums_bmp, DRUMS_W, DRUMS_H, WHITE );
  display.display();
}

void drawSynth() {
  display.clearDisplay();
  display.drawBitmap(16,16, synth_bmp, SYNTH_W, SYNTH_H, WHITE );
  display.display();
}

/**********************************************************************************************/
/* Setup
/**********************************************************************************************/

void setup() {
  //Begin Serial
  SLIPSerial.begin(9600); // baud Rate affects proformance
  //Display Setup
  //Initialized with I2C addr 0x3D or 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  //Splash Intro With Delay(500);
  //splashScreen();
  initPrintText();
  drawLoading();
  //drawDrumSet();
  //drawDrumHit(2);
}

void drawString(int x, int y, int fontSize, char * str) {
  display.clearDisplay();
  display.setTextSize(fontSize);
  display.setCursor(x,y);
  display.print(str);
  
}

void drawShutdown() {
  display.clearDisplay();
  display.setCursor(16,12);
  display.setTextSize(1);
  display.print("Help me I am trapped in here."); 
}


void updateDispSys(OSCMessage &msg)
{
  
  if (msg.isString(0)) {
    int length = msg.getDataLength(0);
    char str[length];
    msg.getString(0,str,length);
    drawString( 16, 16, 1, str );
    //display.print(str);
  }
  if (msg.isInt(0) ) {
    int num = msg.getInt(0);
    
    if ( num == 0 ) {
      drawLoading();
    } else if ( num == -1 ) {
      drawShutdown();
    } else if ( num == 2 ) { 
      drawString(32,32,1,"Daniel Rocks");
    
    } else {
      display.print(num);
    }
  }
  display.display();
  
}
void updateDispSequencer(OSCMessage &msg) {
  if (msg.isInt(0) ) {
    int num = msg.getInt(0);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("sequ");
    display.print(num);
    delay(250);
    
    if (num > -1) {
      drawString(16,12, 2, "squ");
    } else {
      drawString(16,12, 2, ">-1");
    }
  }
}

void updateDispDrums(OSCMessage &msg) {
  if (msg.isInt(0) ) {
    int num = msg.getInt(0);
    if (num > -1) {
      drawDrumHit(num);
    } else {
      drawDrumSet();
    }
  }
}
void updateDispSynth(OSCMessage &msg) {
  if (msg.isInt(0) ) {
    int num = msg.getInt(0);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("synth");
    display.print(num);
    delay(250);
    if (num > -1) {
      drawString(16,12, 4, "squ");
    } else {
     drawSynth();
    //char str[] = String(num);
    
    //char charStr[7];
    //itoa() included stdlib.h
    //itoa(num,buffer,10);
    
    
    }
  }
}

/*
void updateDispSynth(OSCMessage &msg) {
  if (msg.isInt(0) ) {
    int num = msg.getInt(0);
    if (num > -1) {
      // draw note stuff 1 - 24
      drawSynth();
    } else {
      //init synth
       int num = msg.getInt(0);
    //char str[] = String(num);
    
    char charStr[7];
    //itoa() included stdlib.h
    //itoa(num,buffer,10);
    
    drawString(16,12, 4, "synth");  
    }
  }
  drawString(16,12, 4, "synth");  
}
*/

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
  // Send OSC used to be here

  //Dispatch messages
  if(!msgIN.hasError()) {
    msgIN.dispatch("/x" , updateDispSys);
    msgIN.dispatch("/d" , updateDispDrums);
    msgIN.dispatch("/s" , updateDispSynth);
    msgIN.dispatch("/q" , updateDispSequencer);
    
    msgIN.dispatch("/g" , updateDispSynth);
    msgIN.dispatch("/h" , updateDispSequencer);
  }
  
  
  
    
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
  }
  */
  
  
}
