
// * * * * * * * * * RGB LED BEATS * * * * * * * * * * *
// Fashes all LED ligts on a 5050 strip a color.
// Connect 12v 5A powersupply to arduino power plug
// vin in to power on strip

// - -          __Controling RGB LEDS in the strip__
//
// - -   I t    J u s t    T a k e s     a     l i l - l o v e  - -
//
// - -
// Each light is controlled via power rails on the strip
// All lights change at the same time. (hence the beats)
// A PWM signal from arduino controls irf520 mosfets for
// each color of the strip.

//  *note : V1 has only red blue colors

#define REDPIN 3
#define BLUEPIN 6 //  use to be 5
#define GREENPIN 5 // 6

#define BUT1PIN A0
#define BUT2PIN A3
#define BUT3PIN A4
#define BUT4PIN A5

// analog Brightness
#define KNOB1PIN A1

#define FADESPEED 10
#define RATE 1 // 1 smaller step // 5 bigger steps

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  
  pinMode(KNOB1PIN, INPUT);
  
  pinMode(BUT1PIN, INPUT_PULLUP);
  pinMode(BUT2PIN, INPUT_PULLUP);
  pinMode(BUT3PIN, INPUT_PULLUP);
  pinMode(BUT4PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

//  Input Buttons r, g, b, modeSelect
int but1, but2, but3, but4;

// Mode Select
int mode = 0;
// 0 - controll mode
// 1 - auto play
// 2 - set color mode
#define NUMMODES 3


// Timer
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
int stepMillis = 3333;
#define MINSTEP 5
#define MAXSTEP 9999

// step variables
int interval = 10;
int rvalue = 0;
int rstep = 10;

int rValue, gValue, bValue;
int brightness = 100; // Current Brightness of each led 0 - 255 PWM
int ainput = 0;
int analogBrightness = 0; // Reading from knob mapped to 0 - 255
int rBrightness = 10;
int gBrightness = 10;
int bBrightness = 10;

void getInput() {
  but1 = digitalRead(BUT1PIN);
  but2 = digitalRead(BUT2PIN);
  but3 = digitalRead(BUT3PIN);
  but4 = digitalRead(BUT4PIN);

  ainput = analogRead(KNOB1PIN);
  //delay(5); // Maybe Need for more stable
  analogBrightness = map(ainput, 0, 1023, 0 ,255);
  // Sets current LED Brightness
  brightness = analogBrightness;
  
}
void loop() {

  // Update timer
  currentMillis = millis();
  
  
  getInput();


  // Testing
//  Serial.print("dankyny /n");
//  String cock = String(analogBrightness);
//  Serial.print(cock);
  
 // Mode Button Pressed
 if (but4) {
    // nothing
  } else {
    // pressed
    // Mode on
    mode += 1;
    mode = mode % NUMMODES;
//    if( mode == 1 ) {
//      // Exit Automation Mode
//      mode = 0;
//      // Set all on lights to off
////      analogWrite(REDPIN, 0);
////      analogWrite(GREENPIN, 0);
////      analogWrite(BLUEPIN, 0);
//    } else {
//      mode = 1;
//    }


  // flash color to signify Mode change transition
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 0);
  
    if (mode == 0 ) {
      analogWrite(REDPIN, 64);
      delay(100);
      analogWrite(REDPIN, 0);
    } else if (mode ==  1 ) {
      analogWrite(BLUEPIN, 64);
      delay(100);
      analogWrite(BLUEPIN, 0);
    } else { // mode 2
      analogWrite(GREENPIN, 64);
      delay(100);
      analogWrite(GREENPIN, 0);
    }
  }


  // Toggles autoPlay
  if( mode == 1 ) {
    // Do the magical jucy thing. :-D
  
    // check if step time ellapsed
    // do a step
    stepMillis = map(ainput, 0, 1023, MINSTEP, MAXSTEP);
    
    if  (currentMillis - previousMillis >= stepMillis) {
      previousMillis = currentMillis;
  
      // update each color 1 step
      rValue = random(255);
      gValue = random(255);
      bValue = random(255);
      analogWrite(REDPIN, rValue);
      analogWrite(GREENPIN, gValue);
      analogWrite(BLUEPIN, bValue);
      
    }

  } else if (mode == 0) {
    // In controll Mode No automation needed
    // Use button states to light LEDs and turn them off

    if (but1) {
      analogWrite(BLUEPIN, 0);
    } else {
      analogWrite(BLUEPIN, brightness);
    }
  
    if (but2) {
      analogWrite(GREENPIN, 0);
    } else {
      analogWrite(GREENPIN, brightness);
    }
    if (but3) {
      analogWrite(REDPIN, 0);
    } else {
      analogWrite(REDPIN, brightness);
    }

  } else { // mode == 2

    //Set individule brightness 

    if (but1) {
      //analogWrite(BLUEPIN, 0);
    } else {
       rBrightness = analogBrightness; 
       analogWrite(REDPIN, rBrightness);
    }
  
    if (but2) {
      
    } else {
      gBrightness = analogBrightness; 
      analogWrite(GREENPIN, gBrightness);
    }
    if (but3) {
      
    } else {
      bBrightness = analogBrightness; 
      analogWrite(BLUEPIN, bBrightness);
    }
    
  }


}
