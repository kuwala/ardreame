/*
 *******************************************************************************
 * USB-MIDI to Legacy Serial MIDI converter
 * Copyright 2012-2016 Yuuichi Akagawa
 *
 * Idea from LPK25 USB-MIDI to Serial MIDI converter
 *   by Collin Cunningham - makezine.com, narbotic.com
 *
 * for use with USB Host Shield 2.0 from Circuitsathome.com
 * https://github.com/felis/USB_Host_Shield_2.0
 *******************************************************************************
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *******************************************************************************
 */

#include <usbh_midi.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#ifdef USBCON
#define _MIDI_SERIAL_PORT Serial1
#else
#define _MIDI_SERIAL_PORT Serial
#endif
//////////////////////////
// MIDI Pin assign
// 2 : GND
// 4 : +5V(Vcc) with 220ohm
// 5 : TX
//////////////////////////

USB Usb;
USBH_MIDI  Midi(&Usb);
//Daniels
int noteCounter = 0;
unsigned long lastTime;
unsigned long maxTime = 150;
int prevNote = 0;
int myMidi[3];


void MIDI_poll();
void doDelay(unsigned long t1, unsigned long t2, unsigned long delayTime);

void setup()
{
  Serial.begin(115200);
  _MIDI_SERIAL_PORT.begin(31250);

  //Workaround for non UHS2.0 Shield
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  if (Usb.Init() == -1) {
    while (1); //halt
  }//if (Usb.Init() == -1...
  delay( 200 );
}

void loop()
{
  unsigned long t1;

  Usb.Task();
  t1 = micros();
  if ( Usb.getUsbTaskState() == USB_STATE_RUNNING )
  {
    MIDI_poll();
  }
  playNotes();
  //delay(1ms)
  doDelay(t1, micros(), 1000);
}

// Poll USB MIDI Controler and send to serial MIDI
void MIDI_poll()
{
  uint8_t outBuf[ 3 ];

  uint8_t size;

  do {
    if ( (size = Midi.RecvData(outBuf)) > 0 ) {
      //MIDI Output
      _MIDI_SERIAL_PORT.write(outBuf, size);
      //Serial.println(myMidi);
      
    }
  } while (size > 0);
}

void playNotes() {
  int myMidi[3];
  int* ptr = myMidi;
  if (millis() - lastTime > maxTime) {
    lastTime = millis();

    
//    if (noteCounter % 2 == 1) {
//      //Note Off
//      myMidi[0] = 128;
//    } else {
//      // Note On
//      myMidi[0] = 144;
//    }

    // Turn Prev Note off
    myMidi[0] = 128;
    myMidi[1] = prevNote;
    myMidi[2] = 0;
    Midi.SendData(ptr, 0);

    // Turn New Note on
    myMidi[0] = 128;
    myMidi[1] = 10 + noteCounter;
    myMidi[2] = 123; // Velocity
    Midi.SendData(ptr, 0);

    // Save New Note as Prev Note
    prevNote = myMidi[1];
    if (noteCounter > 126) {
      noteCounter = 10;
    } else {
      noteCounter += 1;
    }

//    for(int i = 0; i < 5; i ++ ) {
//      // Set firs Bye to Note on Midi Command
//      myMidi[0] = 144;
//      // Set Note
//      myMidi[1] = 60 + 20*i;
//      Midi.SendData(myMidi, 0);
//      //delay(200);
//      myMidi[0] = 128;
//      Midi.SendData(myMidi, 0);
//      //delay(200);
//      
//    }
  }
}

// Delay time (max 16383 us)
void doDelay(unsigned long t1, unsigned long t2, unsigned long delayTime)
{
  unsigned long t3;

  if ( t1 > t2 ) {
    t3 = (0xFFFFFFFF - t1 + t2);
  } else {
    t3 = t2 - t1;
  }

  if ( t3 < delayTime ) {
    delayMicroseconds(delayTime - t3);
  }
}
