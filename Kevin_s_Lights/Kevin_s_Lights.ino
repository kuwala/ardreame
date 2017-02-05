
void setup() {
  // put your setup code here, to run once:
 
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly: 
  digitalWrite(12, HIGH);
  tone(8, 192);
  delay(250);
  digitalWrite(12, LOW);
  noTone(8);
  delay(75);
  digitalWrite(13, HIGH);
  tone(8, 216);
  delay(250);
  digitalWrite(13, LOW);
  noTone(8);
  delay(75);
  
  digitalWrite(12, HIGH);
  tone(8, 240);
  delay(250);
  digitalWrite(12, LOW);
  noTone(8);
  delay(75);
  digitalWrite(13, HIGH);
  tone(8, 192);
  delay(250);
  digitalWrite(13, LOW);
  noTone(8);
  delay(75);
}
