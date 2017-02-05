int soundPin = 12;
void setup() {
  pinMode(soundPin,OUTPUT);
  
}
int pitchCalc(int n) {
  //n is halfsteps above A4;
  
  //fn = f0 * (a)^n 
  //fo = 440hz // which is A4 above middle C
  //a = (2)1/12 = 1.059463094359
  float a = 1.059463094359;
  return 440 * pow(a, n);  
}
void sound(int pitch, int tdelay ) {
  tone(soundPin, pitch);
  delay(tdelay);
  //noTone(soundPin);
  //delay(tdelay);
}


void loop() {

 for (int i = 0; i < 48; i ++) {
   sound(pitchCalc(i) - 48, 500);
 }

}
