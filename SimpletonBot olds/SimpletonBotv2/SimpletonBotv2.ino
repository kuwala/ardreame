#include <MenuSystem.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 7, 5, 4, 3, 2);
//declare input pins
int but_prev = 9;
int but_next = 10;
int but_cancel = 11;
int but_okay = 12;

unsigned long lastDebounceTime = 0;
int debounceDelay = 5;
int actionDelay = 200;
unsigned long actionTime = 0;

int const nButtons = 4;
int buttons[nButtons] = { 9, 10, 11, 12 };
int buttonsState[nButtons] = { LOW, LOW, LOW, LOW };
int buttonsLast[nButtons] = { LOW, LOW, LOW, LOW };

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




void on_menu_set_feed(MenuItem* pMenuItem)
{
  lcd.setCursor(0,1);
  lcd.print("Eats virus.exe");
  delay(1500);
  
}
void on_menu_set_hack(MenuItem* pMenuItem)
{
  lcd.setCursor(0,1);
  lcd.print("xsds XSD23 43fsd");
  delay(1500);
  
}
void on_menu_set_read(MenuItem* pMenuItem)
{
  lcd.setCursor(0,1);
  lcd.print(genSent());
  delay(1500);

}
void on_menu_set_save(MenuItem* pMenuItem)
{
  lcd.setCursor(0,1);
  lcd.print("error | not savd");
  delay(1500);
  
}

void serialPrintHello()
{
  Serial.println("-----------------------");
  Serial.println("Hello, -Menusystem demo");
}

void displayMenu() {
  lcd.clear();
  printLCDMockUp();
  lcd.setCursor(0,1);
  Menu const* cp_menu = ms.get_current_menu();
  
  //prints current menu name
  
  
  lcd.print(cp_menu->get_selected()->get_name());
}

void setup() {
  //For Debugging
  Serial.begin(9600);
  serialPrintHello();
  
  //inputs
  pinMode(but_prev, INPUT);
  pinMode(but_next, INPUT);
  pinMode(but_cancel, INPUT);
  pinMode(but_okay, INPUT);  
  
  
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
  
}
void handleInput() 
{
  int reading = digitalRead(buttons[1]);
  if (reading != buttonsLast[1]) {
    lastDebounceTime = millis();
  }
  
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
      buttonsState[1] = reading;
      
  }
  buttonsLast[1] = reading;
  
  if ( (millis() - actionTime) > actionDelay) {
    Serial.println(actionTime);
    actionTime = millis();
    
    
    if ( digitalRead(but_prev) == HIGH ) {
      ms.prev();
      displayMenu();
       Serial.println("hadning input 1");
    } else if ( buttonsState[1] == HIGH ) {
      ms.next();
      displayMenu();
       Serial.println("hadning input 2");
    } else if ( digitalRead(but_cancel) == HIGH ) {
      //ms.select();
      displayMenu();
       Serial.println("hadning input 3");
    } else if ( digitalRead(but_okay) == HIGH ) {
      ms.select();
      displayMenu();
       Serial.println("hadning input 4");
    }
    
  }
  
  
}
void printLCDMockUp()
{
  lcd.setCursor(0,0);
  //lcd.print("1234567812345678");
  lcd.print("0x32 0x64 hiya! ");
  
  lcd.setCursor(7,1);
  lcd.print("  (@ _ @)");
}

void serialHandler() {
  char inChar;
  if((inChar = Serial.read())>0) {
    switch (inChar) {
      case 'w': // <-
        ms.prev();
        displayMenu();
        break;
      case 's': // ->
        ms.next();
        displayMenu();
        break;
      case 'd': //select
        ms.select();
        displayMenu();
        break;
      case 'h':
        serialPrintHello();
        break;
      default:
        break;
    }
  }
} // closes serialHandler()



void loop () {
  //serialHandler();
  handleInput();
  
  
  //delay(1000);
}
