#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int const nTexts = 9;

String texts[nTexts] = { "Hello there.", "I like cats.", "Sparkly",
"I need help!", "Praise the sun!", "Doing Good.",
"How are you?", "Keep it up!", "Lets do it!"};

const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply;

void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  lcd.print("Hello Sarah!");
  
  lcd.setCursor(0,1);
  lcd.print("<3 Daniel");
}
void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  int i = random(nTexts);
  lcd.print(texts[i]);
  delay(1000);
  
}
