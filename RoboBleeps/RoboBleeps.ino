/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  
  for (int i = 0; i < 15 ; i ++ ) {
  
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    tone(8, 200 + i*100);
    delay(300 - i *20);               // wait for a second
    digitalWrite(led, LOW);  // turn the LED off by making the voltage LOW
    noTone(8);
    delay(300 - i * 20);               // wait for a second
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    tone(8, 80 + i*100);
    delay(300 - i * 20);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    noTone(8);
    delay(300 - i * 20);               // wait for a second
    
  }
  
  
  for(int i = 1; i < 10; i ++) {
    tone(8, i * 100);
    digitalWrite(led, HIGH);
    delay(108);
  }
  
  for(int i = 1; i < 10; i ++) {
    tone(8, i * 200);
    digitalWrite(led, HIGH);
    delay(108);
  }
  
  for(int i = 1; i < 10; i ++) {
    tone(8, i * 300);
    delay(100.1 * i);
  }
  


  

}
