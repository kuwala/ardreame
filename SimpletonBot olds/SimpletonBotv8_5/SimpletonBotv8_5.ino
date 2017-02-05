#include <MenuSystem.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 7, 5, 4, 3, 2);

byte arduinoCen[8] = {
B00010001,
B00001010,
B00001000,
B00000100,
B00000010,
B00001010,
B00010001,
B00000000
};

byte arduinoMin[8] = {
B00001111,
B00010000,
B00010000,
B00010111,
B00010000,
B00010000,
B00001111,
B00000000
};

byte arduinoPls[8] = {
B00011110,
B00000001,
B00001001,
B00011101,
B00001001,
B00000001,
B00011110,
B00000000
};

byte arduinoLeftEnd[8] = {
B00000000,
B00000000,
B00000000,
B00000001,
B00000001,
B00000000,
B00000000,
B00000000,
};

byte arduinoRightEnd[8] = {
B00000000,
B00000000,
B00000000,
B00010000,
B00010000,
B00000000,
B00000000,
B00000000,
};

byte heartSym[8] = {
B00000000,
B00000000,
B00001010,
B00011111,
B00011111,
B00001110,
B00000100,
B00000000
};

byte eyeGlassesSym[8] = {
B00000000,
B00001110,
B00010001,
B00010101,
B00010101,
B00010001,
B00001110,
B00000000
};

byte eyeDotsSym[8] = {
B00000,
B00000,
B00100,
B00100,
B00000,
B00000,
B00000,
B00000
};

byte eyeClosedSym[8] = {
B00000,
B00000,
B01110,
B00000,
B00000,
B00000,
B00000,
B00000
};

byte mouthClosedSym[8] = { 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00001110,
B00000000,
B00000000,
};

byte mouthOpenSym[8] = { 
B00000000,
B00000000,
B00000000,
B00000000,
B00001110,
B00000100,
B00000000,
B00000000,
};

byte mouthClosedLowSym[8] = { 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00001110,
B00000000,
};

byte eyeGlassesLeftSym[8] = {
B00000000,
B00001110,
B00010001,
B00011001,
B00011001,
B00010001,
B00001110,
B00000000
};


// ** Common Symbols **
byte yenSym = B11111100; // yen
byte microSym = B11100100; // mew - u

// *** Common Strings ***
String clear16 = "                "; // used to clear a row

// !!!!!!!!!!!!! BOYS STATS !!!!!!!!!!!
int boysHunger = 0;
unsigned long boysTimer = 0;
unsigned long boysDelay = 50; // his internal clock tick

// ** Declare input pins **

// For order in buttons array
int const but_prev = 0;
int const but_next = 1;
int const but_cancel = 2;
int const but_okay = 3;

enum button {
  BUT_NULL, // not pressed
  BUT_PREV,
  BUT_NEXT,
  BUT_CANCEL,
  BUT_OKAY
};

int buttonsPin = A0;
int buttonsValue = 0;
button buttonsState2;
int pezoPin = 12;



int const nButtons = 4;
int buttons[nButtons] = { 9, 10, 11, 12 };
int buttonsState[nButtons] = { LOW, LOW, LOW, LOW };

//int buttonsLast[nButtons] = { LOW, LOW, LOW, LOW };
//unsigned long buttonsLastDebounceTime[nButtons] = { 0, 0, 0, 0 };

//unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 0UL; //???????

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
String tVerbs[nVerbs] = { "kicked", "ate", "destroyed", "built" };

int const nNouns = 4;
String tNouns[nNouns] = {"part", "sun", "ship", "boy"};

int const nDeterminant = 4;
String tDeterminant[nDeterminant] = {"the", "a", "my", "your"};

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

MenuSystem ms;
Menu mm("");
MenuItem mi_feed(" Feed ");
MenuItem mi_hack(" Hack ");
MenuItem mi_read(" Read ");
MenuItem mi_save(" Save");
MenuItem mi_hunger( " Hunger");
MenuItem mi_watch(" Watch");


void on_menu_set_hunger(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  lcd.print(clear16);
  lcd.setCursor(0,0);
  lcd.print(" HP : ");
  lcd.print(boysHunger);
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
  } else { // minutes 2 digits
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
  lcd.print(" Khz");
  boysHunger += feed;
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
  Serial.println("S Y N T R O N v2");
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

void setup() { //  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
  //For Debugging
  Serial.begin(9600);
  serialStartUp();
  setupMenu();
  
  //inputs
  for (int i = 0; i < nButtons; i++ ) {
    pinMode(buttons[nButtons], INPUT);
  }
  
 
  loadCharSet1(); // arduino logo
  bootSys();
  loadCharSet2(); // boy face
  lcd.clear();
  //printLCDMockUp();
  welcome();
  displayMenu();

} // end startup()  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **

void getButtonInput2() {
  
  int notes[] = {262, 294, 330, 349};

  buttonsValue = analogRead(buttonsPin);
  if(buttonsValue == 1023) {
    buttonsState2 = BUT_PREV;
    tone(pezoPin, notes[0]);
    
  }else if (buttonsValue >= 990 && buttonsValue <= 1010) {
    tone(pezoPin, notes[1]);
    buttonsState2 = BUT_NEXT;
    
  }else if (buttonsValue >= 505 && buttonsValue <= 515) {
    tone(pezoPin, notes[2]);
    buttonsState2 = BUT_OKAY;
    
  }else if (buttonsValue >= 5 && buttonsValue <= 10) {
    tone(pezoPin, notes[3]);
    buttonsState2 = BUT_CANCEL;
    
  }else {
    noTone(pezoPin);
    buttonsState2 = BUT_NULL;
  }
Serial.println(buttonsValue);  
  
}

void getButtonInput() {
  
  int reading = 0;
  for (int i; i < nButtons; i++) {
    //reading = digitalRead(buttons[i]);
    buttonsState[i] = digitalRead(buttons[i]);
    /* // fucking debounce man!
    // If reading is different reset debounce timer
    if (reading != buttonsLast[i]) {
      buttonsLastDebounceTime[i] = millis();
      //Serial.println("reading difference");
    }
      
   //Set the State if enough time has passed
   if ((millis() - buttonsLastDebounceTime[i]) > debounceDelay) {
     if (reading != buttonsState[i]) {
        buttonsState[i] = reading;
        //Serial.println("B");
     } 
        
    } 
    buttonsLast[i] = reading;
    */
  } // End for
  
} // end getButtonInput();

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
         
      } else if ( buttonsState2 == BUT_NEXT ) { 
        ms.next();
        displayMenu();
        navTime = millis();
        menuState = STATE_NAVCOOLDOWN;
         
      } else if ( buttonsState2 == BUT_CANCEL ) { 
        //ms.select(); // no cancel yet
        displayMenu();
        navTime = millis();
        menuState = STATE_NAVCOOLDOWN;
        
      } else if ( buttonsState2 == BUT_OKAY) {
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



void loop () {
  
  getButtonInput2();
  handleInput();
  updateBoy();
  
}
void updateBoy() {
  if ( ( millis() - boysTimer ) > boysDelay ) {
    boysHunger --;
    boysTimer = millis();
  }
  
}

void bootSys() {
  
  int delayLong = 3000;
  int delayMed = 1000;
  int delayShort = 300;
  
  if (digitalRead(buttons[but_okay]) == HIGH) {
    lcd.setCursor(0,0);
    lcd.print(" TURBO !!");
    delay(delayShort);
    delayLong = 300;
    delayMed = 150;
    delayShort = 100;
  }
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
 
  lcd.print("S Y N T R N v2 ");

  delay(delayMed); 
  
  lcd.setCursor(0,1);
  lcd.print("ATmega328");
  delay(delayMed);
  if (digitalRead(buttons[but_okay]) == HIGH) {
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
  
}
  
  
  
  
void printLCDMockUp()
{

  lcd.setCursor(9,0);
  lcd.print("Hi ");
  lcd.write(4); // <3
  lcd.write(4);
  lcd.write(4);
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
        if( digitalRead (buttons[but_okay]) == HIGH ) {
          waitDelay = 25;
        } else {
          waitDelay = 150;
        }
        delay(waitDelay);
      }
    }
  }
  delay(1000);
}


