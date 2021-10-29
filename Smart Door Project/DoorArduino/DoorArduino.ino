#include "thingProperties.h"
#include <Servo.h>

Servo myservo; 

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  myservo.attach(A1);
}

int pos = 0;
int reedSwitch = 0;

void loop() {
  ArduinoCloud.update();

//Door open
  if(reedSwitch == HIGH){
  for (pos = 0; pos <= openRadius; pos += 1) { // goes from 0 degrees to openRadius degrees
    // in steps of 1 degree
    doorAngle = pos;
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
}
//Door close
    reedSwitch = digitalRead(1);
  
   if(doorClose == HIGH){
    for (pos = openRadius; pos >= 0; pos -= 1) { // goes from openRadius degrees to 0 degrees
    doorAngle = pos ;
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
  }
}

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>


const char THING_ID[] = "6c72221b-7f84-4f6d-b844-2e3ce2a7113b";

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)

void onDoorCloseChange();
void onOpenRadiusChange();

CloudSwitch doorClose;
CloudAngle doorAngle;
CloudAngle openRadius;

void initProperties(){

  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(doorClose, READWRITE, ON_CHANGE, onDoorCloseChange);
  ArduinoCloud.addProperty(doorAngle, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(openRadius, READWRITE, ON_CHANGE, onOpenRadiusChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
