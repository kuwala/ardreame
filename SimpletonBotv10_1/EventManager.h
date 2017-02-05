#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <Arduino.h>
#include "BBoy.h"
#include "Displayer.h"

class EventManager {
  private:
    int eventDelay;
    unsigned long eventTimer;
    BBoy* bBoy;
    Displayer* disp;
    
    static const int numEvents = 4;
    //void (EventManager::*)(int ) eventListPs[numEvents] ; //grrr
    
    //ReturnType (Class::*)(ParameterTypes...)
  
  public:
    EventManager();
    void setBoyDisp(BBoy* _bBoy, Displayer* _disp);
    void update();
    void randEbook();
    void randEat();
    void randLearned();
    void randHurt();
    
    void randEvent();
  
  
};





#endif
