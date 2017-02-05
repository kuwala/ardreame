#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Encoder.h>
// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

//Encoder knob(3, 2);
Encoder knob(21, 22);
Encoder knob2(20, 24);
String huge_ram_tester = "An Arduino board consists of an Atmel 8-bit AVR microcontroller with complementary components that facilitate programming and incorporation into other circuits. An important aspect of the Arduino is its standard connectors, which lets users connect the CPU board to a variety of interchangeable add-on modules known as shields. Some shields communicate with the Arduino board directly over various pins, but many shields are individually addressable via an I²C serial bus—so many shields can be stacked and used in parallel. Official Arduinos have used the megaAVR series of chips, specifically the ATmega8, ATmega168, ATmega328, ATmega1280, and ATmega2560. A handful of other processors have been used by Arduino compatibles. Most boards include a 5 volt linear regulator and a 16 MHz crystal oscillator (or ceramic resonator in some variants), although some designs such as the LilyPad run at 8 MHz and dispense with the onboard voltage regulator due to specific form-factor restrictions. An Arduino's microcontroller is also pre-programmed with a boot loader that simplifies uploading of programs to the on-chip flash memory, compared with other devices that typically need an external programmer. This makes using an Arduino more straightforward by allowing the use of an ordinary computer as the programmer.At a conceptual level, when using the Arduino software stack, all boards are programmed over an RS-232 serial connection, but the way this is implemented varies by hardware version. Serial Arduino boards contain a level shifter circuit to convert between RS-232-level and TTL-level signals. Current Arduino boards are programmed via USB, implemented using USB-to-serial adapter chips such as the FTDI FT232. Some variants, such as the Arduino Mini and the unofficial Boarduino, use a detachable USB-to-serial adapter board or cable, Bluetooth or other methods. (When used with traditional microcontroller tools instead of the Arduino IDE, standard AVR ISP programming is used.)The Arduino board exposes most of the microcontroller's I/O pins for use by other circuits. The Diecimila, Duemilanove, and current Uno provide 14 digital I/O pins, six of which can produce pulse-width modulated signals, and six analog inputs. These pins are on the top of the board, via female 0.10-inch (2.5 mm) headers. Several plug-in application shields are also commercially available. The Arduino Nano, and Arduino-compatible Bare Bones Board and Boarduino boards may provide male header pins on the underside of the board that can plug into solderless breadboards.There are many Arduino-compatible and Arduino-derived boards. Some are functionally equivalent to an Arduino and can be used interchangeably. Many enhance the basic Arduino by adding output drivers, often for use in school-level education to simplify the construction of buggies and small robots. Others are electrically equivalent but change the form factor—sometimes retaining compatibility with shields, sometimes not. Some variants use completely different processors, with varying levels of compatibility. ";

LiquidCrystal lcd(8, 7, 5, 4, 3, 2);

int pitchStep = 0;
int knobDivits = 20;

int buttonState = 0;
int button2State = 0;

int rootNote = -9;
int rootNote2 = 3;
int butInterval = 5;

int pentScaleRes[] = { 2, 4, 7, 9, 12};
int pentScale[] = { 2, 2, 3, 2, 3 };
//int pentScale[] = { 2, 2, 3, 2, 3, 2, 2, 3, 2, 3, 2, 2, 3, 2, 3, 2, 2, 3, 2, 3 };
int knobPos = 0;

int butPin = 4;
int but2Pin = 5;
int piezoPin = 11;
int rLed = 10;
int bLed = 11;
int yLed = 6;
int rLedPwm = 0;
int bLedPwm = 0;


unsigned int long timer = 0;
int delayTime = 400;

int gateOn = 0;
int playNote = 0;
int const gateNumSteps = 11;
int delays[gateNumSteps] = { 800, 400, 200, 100, 50, 25, 13, 7, 4, 2, 1};
int knob2Pos = 0;
int gateStep = 0;


void setup() { 
  
  Serial.begin(9600);
  Serial.println("@kuwala");
  
  pinMode(piezoPin, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  pinMode(yLed, OUTPUT);
  pinMode(butPin, INPUT); // button
}
int notePitchCalc(int n) {
  //n is halfsteps above A4;
  
  //fn = f0 * (a)^n 
  //fo = 440hz // which is A4 above middle C
  //a = (2)1/12 = 1.059463094359
  float a = 1.059463094359;
  return 440 * pow(a, n);  
}


void loop () {
  
 rLedPwm = pitchStep % knobDivits;
 rLedPwm = map(rLedPwm, -20, 20, 0 , 255);
 
 pitchStep = (knob.read() / 4) ;
 gateStep = (knob2.read() / 4);
 
 buttonState = digitalRead(butPin);
 button2State = digitalRead(but2Pin);
 

 
 if( gateStep > 0.) {
   gateOn = 1;
   gateStep = gateStep % gateNumSteps;
   delayTime = delays[gateStep];
 } else {
   gateOn = 0;
 }
 
 if( gateOn == 1 ) {
 
   if ((millis() - timer) > delayTime) {
     
     //Toggle Note
      if (playNote == 0) {
        playNote = 1;
      } else {
        playNote = 0;
      } 
      
      timer = millis();
     
   }
   if ( playNote ) {
       tone(piezoPin, notePitchCalc(pitchStep + (buttonState * 4) + (button2State * 7)));
       digitalWrite(bLed, HIGH);
       digitalWrite(yLed, LOW);
     
   } else {
       noTone(piezoPin);
       digitalWrite(bLed, LOW);
       digitalWrite(yLed, HIGH);
   
   }
   if (buttonState || button2State) {
     digitalWrite(rLed, HIGH);
   } else {
     digitalWrite(rLed, LOW);
   };
   
 } else { // gate mode off so play sound with buttons
   
    if (buttonState == HIGH ) {
       tone(piezoPin, notePitchCalc(pitchStep));
       digitalWrite(bLed, HIGH);
       digitalWrite(yLed, LOW);
       //digitalWrite(rLed, LOW);
       
     } else if (button2State == HIGH) {
       int addOn = pentScaleRes[random(0,5)];
       tone(piezoPin, notePitchCalc(pitchStep + butInterval));
       digitalWrite(rLed, HIGH);
       digitalWrite(yLed, LOW);
     
    
    
    
    } else {
       noTone(piezoPin);
       digitalWrite(bLed, LOW);
       digitalWrite(rLed, LOW);
       digitalWrite(yLed, HIGH);
       
     }
 
 }
   
 
 
 
 
 
 
 //analogWrite(rLed, rLedPwm);
 
 /*
 for( int i = -20; i < 20; i ++ ) {
  tone(8, notePitchCalc(i)); 
  delay(100 + i*2);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  noTone(8);
  delay(100 + i*2);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
 } */
  
}

