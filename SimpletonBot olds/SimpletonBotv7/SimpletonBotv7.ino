#include <MenuSystem.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 7, 5, 4, 3, 2);

byte heartSym[8] = {
B00000000,
B00001010,
B00011111,
B00011111,
B00011111,
B00001110,
B00000100,
B00000000
};

byte eyeGlassesSym[8] = {
B00000000,
B00000000,
B00000000,
B00010101,
B00010001,
B00001110,
B00000000,
B00000000
};

byte eyeDotsSym[8] = {
B00000,
B00000,
B01100,
B01100,
B00000,
B00000,
B00000,
B00000
};

byte eyeLongSym[8] = {
B00000,
B00100,
B00100,
B00100,
B00100,
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

// ** Common Symbols **
byte yenSym = B11111100; // yen 

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
MenuItem mi_save(" Hunger ");

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
  lcd.write(3);
  //delay(1500);
  
}
void on_menu_set_hack(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  lcd.print(clear16);
  
  
  lcd.setCursor(10,1);
  lcd.write(1); // eye glasses
  lcd.setCursor(14,1);
  lcd.write(1); // eye glasses
  
  charExplorer();
  //delay(1500);
  
}
void on_menu_set_read(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  lcd.print(clear16);
  lcd.setCursor(0,0);
  lcd.print(genSent());
  //delay(1500);

}
void on_menu_set_save(MenuItem* pMenuItem) {
  lcd.setCursor(0,0);
  lcd.print(clear16);
  lcd.setCursor(0,0);
  lcd.print(" HP : ");
  lcd.print(boysHunger);
  lcd.print(" Khz");
  lcd.setCursor(12,1);
  lcd.write(3);
  //delay(1500);
  
}

void serialStartUp()
{
  Serial.println("S Y N T R O N v2");
}


void setup() {
  //For Debugging
  Serial.begin(9600);
  serialStartUp();
  
  //inputs
  for (int i = 0; i < nButtons; i++ ) {
    pinMode(buttons[nButtons], INPUT);
  }
  
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
  mm.add_item(&mi_hack, &on_menu_set_hack);
  mm.add_item(&mi_read, &on_menu_set_read);
  mm.add_item(&mi_save, &on_menu_set_save);
  //used for feed options later
  //mu_disp.add_item(&mi_disp_brightness, &on_menu_set_brightness);
  ms.set_root_menu(&mm);
  
  
  lcd.createChar(0, eyeDotsSym);
  lcd.createChar(1, eyeGlassesSym);
  lcd.createChar(2, mouthClosedSym);
  lcd.createChar(3, mouthOpenSym);
  lcd.createChar(4, heartSym); // <3
  lcd.begin(16, 2);
  //charExplorer();
  bootSys();
  lcd.clear();
  printLCDMockUp();
  displayMenu();
  
  
} // end startup()

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
      
      if ( buttonsState[but_prev] == HIGH ) { 
        ms.prev();
        displayMenu();
        navTime = millis();
        menuState = STATE_NAVCOOLDOWN;
         
      } else if ( buttonsState[but_next] == HIGH ) { 
        ms.next();
        displayMenu();
        navTime = millis();
        menuState = STATE_NAVCOOLDOWN;
         
      } else if ( buttonsState[but_cancel] == HIGH ) { 
        //ms.select(); // no cancel yet
        displayMenu();
        navTime = millis();
        menuState = STATE_NAVCOOLDOWN;
        
      } else if ( buttonsState[but_okay] == HIGH ) {
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

void charExplorer() {
  unsigned char c = 0;
  //lcd.blink();
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
      

void loop () {
  
  getButtonInput();
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
  lcd.print("   ( - )( + )    ");
  //lcd.write((byte)0);
  delay(delayLong - delayMed);
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  //byte c = B11110111;
 
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
  lcd.print("Aanalog In ");
  delay(delayShort);
  lcd.print(" 6p ");
  delay(delayMed);
  
  lcd.setCursor(0,1);
  lcd.print(clear16);
  lcd.setCursor(0,1);
  lcd.print("Digitl IO ");
  delay(delayShort);
  lcd.print(" 14p ");
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
void printLCDMockUp()
{

  lcd.setCursor(10,0);
  lcd.write(4); // <3
  lcd.print(" ");
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


