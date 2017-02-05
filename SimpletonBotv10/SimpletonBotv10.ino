#include <MenuSystem.h>
#include <LiquidCrystal.h>
#include "DisplayVars.h"
#include "GlobalVars.h"
#include "BBoy.h"
#include "Displayer.h"

//Custome Class Instunces

LiquidCrystal lcd(8, 7, 5, 4, 3, 2);
BBoy botBoy;
//Used from inside botBoy
Displayer dispTopRight(&lcd,8,0,8);


// ** Declare input pins **

enum button {
  BUT_NULL, // not pressed
  BUT_PREV,
  BUT_NEXT,
  BUT_CANCEL,
  BUT_OKAY
};

int buttonsPin = A0;
int buttonsValue = 0; // analog value
button buttonsState2; // the analog value converted to enum button

// Button Press Notes play C D E G
int notes[] = {
  262, 294, 330, 349};
int pezoPin = 13; // decoy pin 13 ; real pin gets set to 11

// Timer Variables
unsigned long actionDelay = 1500;
unsigned long actionTime = 0;

unsigned long navDelay = 200;
unsigned long navTime = 0;

enum state {
  STATE_NAVCOOLDOWN,
  STATE_IDLE,
  STATE_ACTIONCOOLDOWN
};

state menuState = STATE_IDLE;

//Lots of words and stuff here
int const nVerbs = 4;
String tVerbs[nVerbs] = { 
  "kicked", "ate", "destroyed", "built" };

int const nNouns = 4;
String tNouns[nNouns] = {
  "part", "sun", "ship", "boy"};

int const nDeterminant = 4;
String tDeterminant[nDeterminant] = {
  "the", "a", "my", "your"};


// ***********SETUP BBOY ********************


MenuSystem ms;
Menu mm("");
MenuItem mi_feed(" Feed ");
MenuItem mi_hack(" Hack ");
MenuItem mi_read(" Read ");
MenuItem mi_save(" Save");
MenuItem mi_hunger( " Hunger");
MenuItem mi_watch(" Watch");


void setup() { //  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
  //For Debugging
  Serial.begin(9600);

  serialStartUp();
  setupMenu();
  delay(1000); // checking to see if this helps the lcd not get glitchy chars

  loadCharSet1(); // arduino logo
  secretBoot();
  loadCharSet2(); // boy face
  lcd.clear();
  welcome();
  displayMenu(); // needs changeing
  
  botBoy.setDisplayer(&dispTopRight);
  

} // end startup()  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **

void loop () {


  dispTopRight.update();
  getButtonInput2();
  handleInput();
  botBoy.update();
  //updateBoy();


}



void on_menu_set_hunger(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  lcd.print(clear16);
  lcd.setCursor(0,0);
  lcd.print(" HP : ");
  lcd.print(botBoy.hp);
  lcd.print(" Khz");
  lcd.setCursor(12,1);
  lcd.write(3);

}

void on_menu_set_watch(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  lcd.print(clear16);
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
  lcd.print(clear16);
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
  lcd.print(clear16);
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
  lcd.print(clear16);

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
  lcd.print(clear16);
  lcd.setCursor(0,0);
  lcd.print("E R R O R  4 0 4");

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


void serialStartUp()
{
  Serial.println("Z Y T L O R O N ");
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
  mm.add_item(&mi_feed, &on_menu_set_feed);
  mm.add_item(&mi_read, &on_menu_set_read);
  mm.add_item(&mi_save, &on_menu_set_save);
  mm.add_item(&mi_hack, &on_menu_set_hack);
  mm.add_item(&mi_hunger, &on_menu_set_hunger);
  mm.add_item(&mi_watch, &on_menu_set_watch);
  //used for feed options later
  //mu_disp.add_item(&mi_disp_brightness, &on_menu_set_brightness);
  ms.set_root_menu(&mm);
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

  lcd.clear();
  printLCDMockUp();

  lcd.setCursor(0,1);
  Menu const* cp_menu = ms.get_current_menu();
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
      //ms.select(); // no cancel yet
      displayMenu();
      navTime = millis();
      menuState = STATE_NAVCOOLDOWN;

    } 
    else if ( buttonsState2 == BUT_OKAY) {
      ms.select();
      actionTime = millis(); // set the delay timer
      menuState = STATE_ACTIONCOOLDOWN;
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
    lcd.print( "    Y A Y ! ");

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
  lcd.setCursor(0,0);
  lcd.print(" A R D I U N O ");

  lcd.setCursor(0,1);
  lcd.print("      ");
  //lcd.write((byte)0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  //lcd.write(4);

  delay(delayLong - delayMed);

  lcd.clear();

  lcd.setCursor(0,0);

  lcd.print("Z Y T L O R O N ");

  delay(delayMed); 

  lcd.setCursor(0,1);
  lcd.print("ATmega328");
  delay(delayMed);
  getButtonInput2();
  noTone(pezoPin);
  if ( buttonsState2 == BUT_OKAY ) {
    lcd.setCursor(0,1);
    lcd.print(" TURBO !!");
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
  lcd.print("2KB  ");
  delay(delayMed);

  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  lcd.print("EEPROM  ");
  delay(delayShort);
  lcd.print("1KB  ");
  delay(delayMed);

  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  lcd.print("Flash   ");
  delay(delayShort);
  lcd.print("32KB ");
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
  lcd.write(betaSym);
  lcd.print("etBIOS ");
  delay(delayShort);
  lcd.print("V6.8 ");
  delay(delayMed);


  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  lcd.blink();
  lcd.print("Booting ");
  delay(delayShort);
  lcd.print("System ");
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

  lcd.setCursor(9,0);
  lcd.print("Hi ");
  delay(delayShort);
  lcd.write(4); // <3
  delay(delayShort);
  lcd.write(4);
  delay(delayShort);
  lcd.write(4);
  delay(delayShort);

  lcd.setCursor(1,1);
  lcd.print("Menu");
  delay(delayShort);
  lcd.setCursor(9,0);
  lcd.print("   ");


}



void printLCDMockUp()
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

void charExplorer() {
  unsigned char c = 0;
  int waitDelay = 150;
  while ( c <= 254 ) {
    for ( int y = 0; y < 2; y ++ ) {
      for ( int x = 0; x < 8; x ++ ) {
        lcd.setCursor( x, y );
        lcd.write(c);
        if( c == 255) {
          break;
        }
        c++;
        Serial.println((int)c);
        if( true ) {
          waitDelay = 25;
        } 
        else {
          waitDelay = 150;
        }
        delay(waitDelay);
      }
    }
  }
  delay(1000);
}

/* Sentence Grammer
 
 a = article
 
 s -> np vp
 np -> I | he | she | np
 np -> det n | n
 vp -> v np | v
 det -> a | the | my | his
 n -> boy | cat
 v -> kicked | ate
 
 */

String genSent() {
  /*
  String np = genNP();
   String first = String(np[0,1]);
   np = String(first.toUpperCase() + String(np.substring(1)));
   */
  return " " + genNP() + " " + genVP() + ".";
}
String genNP() {
  int i = random(nNouns);
  return tNouns[i];
}
String genVP() {
  int i = random(nVerbs);
  return tVerbs[i];
}



