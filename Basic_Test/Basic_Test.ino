
int x = 12;
void setup() {
   
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void toggle(int y) {
  
  
  
  digitalWrite(y, HIGH);
  delay(100);
  digitalWrite(y, LOW);
  delay(100);
  
  
}

void loop() {
  
  toggle(12);
  delay(1000);
  toggle(13);
  delay(1000);
  
}

