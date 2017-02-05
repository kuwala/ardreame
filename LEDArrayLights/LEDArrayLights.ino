#include <NewPing.h>


int waitTime = 80;
int lightState = 0; // 0 - off, 1 - on
unsigned long timer = 0;

#define TRIGGER_PIN  A2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MAX_LEDS 10      // How Many LEDs there are
#define LED_START_PIN 2  // The pin the LEDs start and increase by 1

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  // put your setup code here, to run once:

  for(int i = 0; i < MAX_LEDS; i ++ ) {
    pinMode(LED_START_PIN + i, OUTPUT);
    digitalWrite(LED_START_PIN + i, LOW);
  }
  Serial.begin(115200);

}

void loop() {
  //waitTime = sonar.ping_cm();
  //flashLights();
  // Distnace tied to lights ;(
  //int dist = sonar.ping_median(3);
  //dist = sonar.convert_cm(dist);
  int dist = sonar.ping_cm();
  if (dist > 0 ) {
    int numLights = map(dist, 30, MAX_DISTANCE - 50, 0, MAX_LEDS);
    lightLeds(numLights); 
  }
//  Serial.print(sonar.ping_cm());
//  Serial.println(" cm");
  delay(5);

}

void flashLights() {
    // put your main code here, to run repeatedly:
    
  if (millis() - timer > waitTime) {
    if (lightState == 0) {
      for(int i = 0; i < MAX_LEDS; i ++ ) {
        digitalWrite(LED_START_PIN + i, HIGH);
      }
     lightState = 1;
    }
    else if (lightState == 1) {
      for(int i = 0; i < MAX_LEDS; i ++ ) {
        digitalWrite(LED_START_PIN + i, LOW);
      }
      lightState = 0;
    }
    timer = millis();
  } // end timer if
}

void lightLeds(int numLights) {
  // light up the leeeeds
  // dim leds first
  for(int i = 0; i < MAX_LEDS; i ++ ) {
    digitalWrite(LED_START_PIN + i, LOW);
  }

  for(int i = 0; i < numLights; i ++ ) {
    digitalWrite(LED_START_PIN + i, HIGH);
  }
}

