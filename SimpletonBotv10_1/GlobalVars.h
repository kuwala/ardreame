#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include <Arduino.h>
#include "BBoy.h"
#include "EventManager.h"

String static coolStoryTXT = "( cool story bro )";
String static statusTestTxt = "XP: 12 HP: 10/10 Power: 3/6 " + String(char(4)) + ": 3";
String static moodTestTxt = "The boy is Content";
String static spaces8Txt = "        ";

#define DELAYSHORT  300
#define DELAYMED  1000
#define DELAYLONG  2000

enum button {
  BUT_NULL, // not pressed
  BUT_PREV,
  BUT_NEXT,
  BUT_CANCEL,
  BUT_OKAY
};

enum state {
  STATE_NAVCOOLDOWN,
  STATE_IDLE,
  STATE_ACTIONCOOLDOWN
};


//Custome Class Instunces
BBoy botBoy;
Menu const * cp_menu; 
state menuState = STATE_IDLE;
EventManager eventMan;


int buttonsPin = A0; // input
int buttonsValue = 0; // analog value
button buttonsState2; // the analog value converted to enum button




// Timer Variables
unsigned long actionDelay = 1500;
unsigned long actionTime = 0;

unsigned long navDelay = 200;
unsigned long navTime = 0;







// Button Press Notes play C D E G
int notes[] = {
  262, 294, 330, 349};
int pezoPin = 13; // decoy pin 13 ; real pin gets set to 11



//For Setence Gen --- to be Moved Later
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
  


String genNP() {
  int i = random(nNouns);
  return tNouns[i];
}
String genVP() {
  int i = random(nVerbs);
  return tVerbs[i];
}
String genSent() {
  /*
  String np = genNP();
   String first = String(np[0,1]);
   np = String(first.toUpperCase() + String(np.substring(1)));
   */
  return " " + genNP() + " " + genVP() + ".";
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


#endif
