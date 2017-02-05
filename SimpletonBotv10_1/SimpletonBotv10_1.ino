#include <MenuSystem.h>
#include <LiquidCrystal.h>
#include <Arduino.h>
#include "DisplayVars.h" // and lcd and Displayers
#include "GlobalVars.h" 
//#include "BBoy.h"
#include "Displayer.h"
#include "MenuBusiness.h"




// ***********SETUP BBOY ********************



void setup() { //  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
  //For Debugging
  Serial.begin(9600);
  //Can be off if need 
  //no none-randomness for debugging
  //randomSeed(analogRead(A15));
  

  serialStartUp();
  setupMenu();
  //delay(1000); // checking to see if this helps the lcd not get glitchy chars

  loadCharSet1(); // arduino logo
  secretBoot();
  loadCharSet2(); // boy face
  lcd.clear();
  welcome();
  displayMenu(); // needs changeing
  
  botBoy.setDisplayer(&dispTopRight);
  eventMan.setBoyDisp(&botBoy, &dispTopRight);
  dispTopRight.newTextScrolling(&hungryTxt, MEDDELAY);
  

} // end startup()  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **

void loop () {

  //Display Sections
  dispTopRight.update();
  dispTopLeft.update();
  
  
  getButtonInput2();
  handleInput();
  
  //Boy
  botBoy.update();
  
  //EventManager
  eventMan.update();
  


}


void serialStartUp()
{
  Serial.println("K A N G A S K O N ");
  Serial.println("@kuwala");
}



void getButtonInput2() {

  int notes[] = {
    262, 294, 330, 349  };

  buttonsValue = analogRead(buttonsPin);
  if(buttonsValue == 1023) {
    buttonsState2 = BUT_PREV;
    tone(pezoPin, notes[0]);

  }
  else if (buttonsValue >= 990 && buttonsValue <= 1010) {
    tone(pezoPin, notes[1]);
    buttonsState2 = BUT_NEXT;

  }
  else if (buttonsValue >= 505 && buttonsValue <= 515) {
    tone(pezoPin, notes[2]);
    buttonsState2 = BUT_OKAY;

  }
  else if (buttonsValue >= 5 && buttonsValue <= 10) {
    tone(pezoPin, notes[3]);
    buttonsState2 = BUT_CANCEL;

  }
  else {
    noTone(pezoPin);
    buttonsState2 = BUT_NULL;
  }

  //Serial.println(buttonsValue);

}


void displayMenu() {
  //lcd.clear();
  botBoy.drawFace(&lcd);

  lcd.setCursor(0,1); // can be optimized
  lcd.print(spaces8Txt); // clear 8 chars
  
  lcd.setCursor(0,1);
  //Menu const* cp_menu = ms.get_current_menu();
  cp_menu = ms.get_current_menu();
  //prints current menu name
  lcd.print(cp_menu->get_selected()->get_name());

} // End displayMenu()

void handleInput()
{
  switch (menuState) 
  {
  case STATE_IDLE:

    if ( buttonsState2 == BUT_PREV ) { 
      ms.prev();
      displayMenu();
      navTime = millis();
      menuState = STATE_NAVCOOLDOWN;

    } 
    else if ( buttonsState2 == BUT_NEXT ) { 
      ms.next();
      displayMenu();
      navTime = millis();
      menuState = STATE_NAVCOOLDOWN;

    } 
    else if ( buttonsState2 == BUT_CANCEL ) { 
      ms.back(); // no cancel yet
      displayMenu();
      navTime = millis();
      menuState = STATE_NAVCOOLDOWN;

    } 
    else if ( buttonsState2 == BUT_OKAY) {
      
      ms.select();
      Serial.println(cp_menu->get_selected()->get_name());
      if( cp_menu->get_selected()->get_name() == " Feed ") {
        navTime = millis();
        menuState = STATE_NAVCOOLDOWN;
        displayMenu();
      } else {
        actionTime = millis(); // set the delay timer
        menuState = STATE_ACTIONCOOLDOWN;
      }
    }

    break;

  case STATE_NAVCOOLDOWN: // short cool down
    if ( ( millis() - navTime ) > navDelay) {
      menuState = STATE_IDLE;
    }

    break;

  case STATE_ACTIONCOOLDOWN: // long cool down
    if ( ( millis() - actionTime ) > actionDelay ) {
      displayMenu();
      menuState = STATE_IDLE;
    }    
    break;

  } // end switch

} // end of handleInput2()




void secretBoot() {
  getButtonInput2();
  if ( buttonsState2 == BUT_OKAY ) {
    bootSys();
  } 
  else if ( buttonsState2 == BUT_CANCEL ) {
    // be sure to turn of anyTone on previous pin
    // or no sound will play on new pin
    noTone(pezoPin); 
    pezoPin = 11;
    tone(pezoPin, 44);
    lcd.setCursor(0,0);
    lcd.print("P e i z o M o d e ");
    lcd.setCursor(0,1);
    delay(250);
    noTone(pezoPin);
    lcd.print( "    Z A Z ! ");

    delay(500);
  } 
  else if ( buttonsState2 == BUT_PREV ) {


    bootSys();
  }
}

void bootSys() {

  int delayLong = 3000;
  int delayMed = 1000;
  int delayShort = 300;
  //getButtonInput2();
  noTone(pezoPin);
  /*if ( buttonsState2 == BUT_OKAY ) {
   lcd.setCursor(0,0);
   lcd.print(" TURBO !!");
   delay(delayShort);
   delayLong = 300;
   delayMed = 150;
   delayShort = 100;
   } */
   
   pezoPin = 11;
   int x =0;
   for( int i = 300; i < 316; i++) {
     x = (i % 300);
     lcd.setCursor(x,0);
     lcd.print("#");
     lcd.setCursor(x,1);
     lcd.print("#");
    tone(pezoPin, i );
   delay(32 ); 
     noTone(pezoPin);
     delay(8 +  ((i % 300) * 8)); 
   }
   
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" A R D I U N O ");
  tone(pezoPin, notes[3]); //g
  delay(512);
  noTone(pezoPin);
  lcd.setCursor(0,1);
  lcd.print("      ");
  //lcd.write((byte)0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  //lcd.write(4);

  delay(delayLong - delayMed);
  noTone(pezoPin);
  lcd.clear();

  lcd.setCursor(0,0);

  lcd.print("A R D R E A M O ");
  
  tone(pezoPin, notes[3]); //g
  delay(256);
  noTone(pezoPin);
  

  delay(delayMed); 

  lcd.setCursor(0,1);
  lcd.print("ATmega2560");
  
  tone(pezoPin, notes[2]); //g
  delay(256);
  noTone(pezoPin);
  
  delay(delayMed);
  getButtonInput2();
  noTone(pezoPin);
  if ( buttonsState2 == BUT_OKAY ) {
    lcd.setCursor(0,1);
    lcd.print(" TURBO !! ");
    delay(1000);
    delayLong = 300;
    delayMed = 150;
    delayShort = 100;
  }
  lcd.print(" 16Mhz  ");
  delay(delayMed);

  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  lcd.print("SRAM    ");
  delay(delayShort);
  lcd.print("8KB  ");
  delay(delayMed);

  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  lcd.print("EEPROM  ");
  delay(delayShort);
  lcd.print("4KB  ");
  delay(delayMed);

  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  lcd.print("Flash   ");
  delay(delayShort);
  lcd.print("256KB ");
  delay(delayMed);

  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  lcd.print("HD44780 ");
  delay(delayShort);
  lcd.print("ROM A00 ");
  delay(delayMed);

  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  byte betaSym = B11100010; // beta symbol
  //lcd.write(betaSym);
  lcd.print("Danny-BIOS ");
  
  tone(pezoPin, notes[2]); //g
  delay(256);
  noTone(pezoPin);
  
  delay(delayShort);
  lcd.print("V6.8 ");
  delay(delayMed);
  delay(delayMed);


  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  lcd.blink();
  lcd.print("Booting ");
  
  tone(pezoPin, notes[1]); //g
  delay(256);
  noTone(pezoPin);
  
  delay(delayShort);
  lcd.print("System ");
  
  tone(pezoPin, notes[0]); //g
  delay(256);
  noTone(pezoPin);
  
  delay(delayMed);

  /*
  // draws random symbols from (0,10) - (0,16)
   int nMin = 9;
   int nMax = 14;
   int nPos = 9;
   byte sym = 200;
   byte symMin = 205;
   byte symMax = 244;
   for (int i = 0; i < 36; i++) {
   if (nPos > nMax) { nPos = nMin ; }
   if ( sym > symMax) { sym = symMin; }
   
   nPos+=2;
   sym++;
   lcd.setCursor(nPos,0);
   lcd.write(sym);
   delay(100);
   
   }
   */

  //final delay

  delay(delayLong);
  lcd.noBlink();
}

void randomWelcomeMessage() {
  
  int rand = random(5);
  switch(rand) {
    
    case 0:
      lcd.setCursor(9,0);
      lcd.print("Hi ");
      delay(DELAYMED);
      
      break;
      
    case 1:
      lcd.setCursor(11,0);
      lcd.write(4); // <3
      delay(DELAYSHORT);
      lcd.write(4);
      delay(DELAYSHORT);
      lcd.write(4);
      delay(DELAYSHORT);
      
      break;
    
    case 2:
      lcd.setCursor(9,0);
      lcd.print("  zZz");
      delay(DELAYMED);
    
      break;
      
    case 3:
    case 4:
      lcd.setCursor(9,0);
      lcd.write(random(128,255));
      delay(DELAYSHORT);
      lcd.write(random(128,255));
      delay(DELAYSHORT);
      lcd.print(" woah!");
      delay(DELAYMED);
      
      break;
      
    default:
      lcd.setCursor(9,0);
      lcd.print("woah!");
      delay(DELAYMED);
      
      break;
  }//end switch
  
}

void welcome() {
  int delayMed = 1000;
  int delayShort = 300;

  lcd.setCursor(7,1);
  lcd.print("  (");
  //lcd.write(B10100101); // drawys dot eye;
  lcd.setCursor(12,1);
  lcd.write(2); // mouth
  lcd.setCursor(15,1);
  lcd.print(")");

  lcd.setCursor(10,1);
  lcd.write(5); // eye closed
  lcd.setCursor(14,1);
  lcd.write(5); // eye closed

  delay(delayShort);

  lcd.setCursor(10,1);
  lcd.write((byte)0); // eye closed
  lcd.setCursor(14,1);
  lcd.write((byte)0); // eye closed




  delay(delayShort);

  randomWelcomeMessage();

  lcd.setCursor(1,1);
  lcd.print("Menu");
  delay(delayShort);
  lcd.setCursor(9,0);
  lcd.print("   ");


}



void printLCDMockUp() // OLD DELETE ME PLEASE  ----------------------OBSOLET CODE---------------------------
{

  /*
  // display hello
   lcd.setCursor(9,0);
   lcd.print("Hi ");
   lcd.write(4); // <3
   lcd.write(4);
   lcd.write(4);
   */

  botBoy.drawFace(&lcd);

  /*
  // display boys face
   lcd.setCursor(7,1);
   lcd.print("  (");
   //lcd.write(B10100101); // drawys dot eye;
   lcd.write((byte)0);
   //lcd.print(" _ ");
   lcd.print(" ");
   lcd.write(2);
   lcd.print(" ");
   lcd.write((byte)0);
   //lcd.write(B10100101); // drawys dot eye;
   //lcd.write((byte)0); // draws closed eye
   lcd.print(")");
   */

}






