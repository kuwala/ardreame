#ifndef MENUBUSINESS_H
#define MENUBUSINESS_H

#include <Arduino.h>
#include <LiquidCrystal.h>
// For topLeftDisp
#include "DisplayVars.h"

/* A bunch of functions and shit
   for setting up the menu

*/


MenuSystem ms;
Menu mm("");
MenuItem mi_feed(" Feed ");
MenuItem mi_hack(" Hack ");
MenuItem mi_read(" Read ");
MenuItem mi_save(" Save");
MenuItem mi_hunger( " Hunger");
MenuItem mi_status( " Status");
MenuItem mi_watch(" Watch");

Menu mfeed(" Feed ");
MenuItem mi_apple("Apple");
MenuItem mi_freq("Freq");
MenuItem mi_volt("Volts");
MenuItem mi_chip("Chip");

String TEMPTEXT;




void on_menu_set_status(MenuItem* pMenuItem) {
  //dispTopLeft.newTextScrolling(&statusTestTxt, 500);
  dispTopLeft.newTextScrolling(&moodTestTxt, 500);
  
  
}


void on_menu_set_hunger(MenuItem* pMenuItem) {
  /*
  lcd.setCursor(0,0);
  lcd.print(clear8);
  lcd.setCursor(0,0);
  lcd.print(" HP : ");
  lcd.print(botBoy.hp);
  lcd.print(" Khz");
  */
  //lcd.setCursor(12,1);
  //lcd.write(3);
  //lcd.write(1);
  TEMPTEXT = String(" HP : "+ String(botBoy.hp) + " "+ String(char(1)) + "& Lots of kittens");
  dispTopRight.newTextScrolling(&TEMPTEXT, 500);
  //lcd.print("H"+String(char(1)) + "Lots of kittens");

}

void on_menu_set_watch(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  //lcd.print(clear8);
  lcd.setCursor(0,0);

  lcd.print("C A S I O");
  lcd.setCursor(1,1);
  int totalSecs = millis() / 1000;
  int seconds = totalSecs % 60;
  int minutes = totalSecs / 60;
  char extraZero =0;
  if (minutes < 10) {
    lcd.print("0" + String(minutes) + " : " + String(seconds));
  } 
  else { // minutes 2 digits
    lcd.print( String(minutes) + " : " + String(seconds));
  }

}

void on_menu_set_feed(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  lcd.print(clear8);
  lcd.setCursor(0,0);
  lcd.print("Eats ");
  int feed = random(20, 2000);
  lcd.print(feed);
  tone(pezoPin, feed);
  delay(400);
  lcd.print(" Hz");
  botBoy.feed(1); // feed 1 hp to bot boy
  lcd.setCursor(12,1);
  lcd.write(3); // mouth opened

  lcd.setCursor(10,1);
  lcd.write(5); // eye closed
  lcd.setCursor(14,1);
  lcd.write(5); // eye closed
  //delay(1500);

}
void on_menu_set_hack(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  lcd.print(clear8);
  noTone(pezoPin);


  lcd.setCursor(10,1);
  lcd.write(1); // eye glasses
  lcd.setCursor(14,1);
  lcd.write(1); // eye glasses

  //charExplorer();
  //testing();
  //charExplorer();
  //delay(1500);

}
void on_menu_set_read(MenuItem* pMenuItem) {
  noTone(pezoPin);
  int delayMed = 500;
  lcd.setCursor(0,0);
  lcd.print(clear8);

  lcd.setCursor(10,1);
  lcd.write(7); // eye glasses

  lcd.setCursor(12,1);
  lcd.write(6); // mouth closed low

  lcd.setCursor(14,1);
  lcd.write(7); // eye glasses

  lcd.setCursor(0,0);
  lcd.print(genSent());

  delay(delayMed);

  lcd.setCursor(10,1);
  lcd.write(1); // eye glasses left

  lcd.setCursor(14,1);
  lcd.write(1); // eye glasses left

  delay(delayMed);

  lcd.setCursor(10,1);
  lcd.write(7); // eye glasses left

  lcd.setCursor(14,1);
  lcd.write(7); // eye glasses left



}
void on_menu_set_save(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  lcd.print(clear8);
  lcd.setCursor(0,0);
  lcd.print("E R R O R  4 0 4");

}

void on_menu_set_apple(MenuItem * pMenuItem) {

}

void on_menu_set_freq(MenuItem* pMenuItem) {
    lcd.setCursor(0,0);
  lcd.print(clear8);
  lcd.setCursor(0,0);
  lcd.print("Eats ");
  int feed = random(10, 4000);
  lcd.print(feed);
  tone(pezoPin, feed);
  delay(400);
  lcd.print(" Hz");
  botBoy.feed(1); // feed 1 hp to bot boy
  lcd.setCursor(12,1);
  lcd.write(3); // mouth opened

  lcd.setCursor(10,1);
  lcd.write(5); // eye closed
  lcd.setCursor(14,1);
  lcd.write(5); // eye closed
  
}

void on_menu_set_volt(MenuItem* pMenuItem) {
  
}

void on_menu_set_chip(MenuItem* pMenuItem) {
  
}

void loadCharSet1() {
  // (-)(+)
  lcd.createChar(0, arduinoLeftEnd); 
  lcd.createChar(1, arduinoMin);
  lcd.createChar(2, arduinoCen);
  lcd.createChar(3, arduinoPls);
  lcd.createChar(4, arduinoRightEnd); 

  lcd.begin(16,2);

}

void loadCharSet2() {
  // ( . _ . )
  // ( u _ u )
  lcd.createChar(0, eyeDotsSym);
  lcd.createChar(1, eyeGlassesSym);
  lcd.createChar(2, mouthClosedSym);
  lcd.createChar(3, mouthOpenSym);
  lcd.createChar(4, heartSym); // <3
  lcd.createChar(5, eyeClosedSym);
  lcd.createChar(6, mouthClosedLowSym);
  lcd.createChar(7, eyeGlassesLeftSym);

  lcd.begin(16,2);
}


void setupMenu() {

  //Put the Menu Together
  /*
  Menu Structure
   -Set_Time
   -Set_Date
   -Set_Alarm
   -Menu_Disp
   --Set_Display
   
   */
  //mm.add_item(&mi_feed, &on_menu_set_feed);
  mm.add_item(&mi_read, &on_menu_set_read);
  mm.add_menu(&mfeed);
  mfeed.add_item(&mi_apple, &on_menu_set_apple);
  mfeed.add_item(&mi_freq, &on_menu_set_freq);
  mfeed.add_item(&mi_volt, &on_menu_set_volt);
  mfeed.add_item(&mi_chip, &on_menu_set_chip);
  mm.add_item(&mi_save, &on_menu_set_save);
  mm.add_item(&mi_hack, &on_menu_set_hack);
  mm.add_item(&mi_hunger, &on_menu_set_hunger);
  mm.add_item(&mi_status, &on_menu_set_status);
  mm.add_item(&mi_watch, &on_menu_set_watch);
  
  
  //used for feed options later
  //mu_disp.add_item(&mi_disp_brightness, &on_menu_set_brightness);
  ms.set_root_menu(&mm);
}


#endif
