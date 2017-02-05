#include <MenuSystem.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 7, 5, 4, 3, 2);

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
MenuItem mi_feed("[ Feed >");
MenuItem mi_hack("< Hack >");
MenuItem mi_read("< Read >");
MenuItem mi_save("< Save ]");

void on_menu_set_feed(MenuItem* pMenuItem) {
  lcd.setCursor(0,1);
  lcd.print("Eats virus.exe");
  //delay(1500);
  
}
void on_menu_set_hack(MenuItem* pMenuItem) {
  lcd.setCursor(0,1);
  lcd.print("xsds XSD23 43fsd");
  //delay(1500);
  
}
void on_menu_set_read(MenuItem* pMenuItem) {
  lcd.setCursor(0,1);
  lcd.print(genSent());
  //delay(1500);

}
void on_menu_set_save(MenuItem* pMenuItem) {
  lcd.setCursor(0,1);
  lcd.print("error | not savd");
  //delay(1500);
  
}

void serialPrintHello()
{
  Serial.println("-----------------------");
  Serial.println("Hello, -Menusystem demo");
}


void setup() {
  //For Debugging
  Serial.begin(9600);
  serialPrintHello();
  
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
  
  
  lcd.begin(16, 2);
  lcd.print("LCD ON!");
  delay(700);
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
      

void loop () {
  
  getButtonInput();
  handleInput();
  
}
void printLCDMockUp()
{
  lcd.setCursor(0,0);
  lcd.print("0x32 0x64 0x86 HEX! ");
  
  lcd.setCursor(7,1);
  lcd.print("  (+ x +)");
}


