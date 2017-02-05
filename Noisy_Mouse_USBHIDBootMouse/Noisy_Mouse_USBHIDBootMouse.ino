#include <hidboot.h>
#include <usbhub.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif


 #define ENABLE_UHS_DEBUGGING 1
//Daniels Add on
int pezo = 8;
int toneOn = 0;
int pitch = 300;
int led = 3;



class MouseRptParser : public MouseReportParser
{
protected:
	virtual void OnMouseMove	(MOUSEINFO *mi);
	virtual void OnLeftButtonUp	(MOUSEINFO *mi);
	virtual void OnLeftButtonDown	(MOUSEINFO *mi);
	virtual void OnRightButtonUp	(MOUSEINFO *mi);
	virtual void OnRightButtonDown	(MOUSEINFO *mi);
	virtual void OnMiddleButtonUp	(MOUSEINFO *mi);
	virtual void OnMiddleButtonDown	(MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{
    pitch += mi->dX * 3;
    if (pitch < 0) {
      pitch = pitch * -1 ;
    }
    Serial.println("pitch: " + String(pitch));
    Serial.print("dx=");
    Serial.print(mi->dX, DEC);
    Serial.print(" dy=");
    Serial.println(mi->dY, DEC);
};
void MouseRptParser::OnLeftButtonUp	(MOUSEINFO *mi)
{
    toneOn = 0;
    digitalWrite(led, LOW);
    Serial.println("L Butt Up");
};
void MouseRptParser::OnLeftButtonDown	(MOUSEINFO *mi)
{
    toneOn = 1;
    digitalWrite(led, HIGH);
    Serial.println("L Butt Dn");
};
void MouseRptParser::OnRightButtonUp	(MOUSEINFO *mi)
{
    Serial.println("R Butt Up");
};
void MouseRptParser::OnRightButtonDown	(MOUSEINFO *mi)
{
    Serial.println("R Butt Dn");
};
void MouseRptParser::OnMiddleButtonUp	(MOUSEINFO *mi)
{
    Serial.println("M Butt Up");
};
void MouseRptParser::OnMiddleButtonDown	(MOUSEINFO *mi)
{
    Serial.println("M Butt Dn");
};

USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

uint32_t next_time;

MouseRptParser                               Prs;

void setup()
{
    Serial.begin( 115200 );
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
    Serial.println("Start");

    if (Usb.Init() == -1)
        Serial.println("OSC did not start.");

    delay( 200 );

    next_time = millis() + 5000;

    HidMouse.SetReportParser(0,(HIDReportParser*)&Prs);
    pinMode(led, OUTPUT);
}

void loop()
{
  //Serial.println("Trying things");
  Usb.Task();
  if (toneOn == 1) {
    tone(pezo, pitch);
  } else {
    noTone(pezo);
  }
}

