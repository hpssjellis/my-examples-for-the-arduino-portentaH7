#include "pinDefinitions.h"

int myDelay = 300;   // non-block delay in milliseconds
unsigned long myStart; 
bool  mySwitch = false; 
int myPin = 0;

String myPinNameFunction(int thePin){
  int realPin = digitalPinToPinName(thePin) % ALT0;
  if (realPin == NC) {
    return "Not a pin";
  }
  String extra = "";
  switch (digitalPinToPinName(thePin) & DUAL_PAD) {
    case 0:
      break;
    case ALT0:
      extra = "ALT0";
      break;
    case ALT1:
      extra = "ALT1";
      break;
    case ALT2:
      extra = "ALT2";
      break;
    case DUAL_PAD:
      extra = "_C";
      break;
  }
  return "P" + String(char('A' + (realPin / 16))) +"_" + String(realPin % 16) + extra;
}

void setup() {
  Serial.begin(115200);
  myStart = millis();   // set delay
  while (!Serial || millis() < 10000) {}  // wait for Serial or 10 seconds

   // This tests each pinName converts to pin index
   // Serial.println("Pin PH_15: " + String(PinNameToIndex(PH_15)) );

   // This shows all index's as pin names
   for (int myLoop=0; myLoop<=195; myLoop++){
      String myName = myPinNameFunction(myLoop);
      PinName myIn  = digitalPinToPinName(myLoop);
      int myIndex   = PinNameToIndex(myIn);
      Serial.println("Pin Index " + String(myLoop) + ": " + myName + ", Back to pin index: " + String(myIndex)+ "    " );
   }
   Serial.println("-----------------------------");

  pinMode(LEDB, OUTPUT);
}

void loop() { 

   if ( (millis() - myStart ) >= myDelay) {       
      myStart = millis();      //  reset the delay time
      myPin++;
      if (myPin >= 193) {myPin = 0;}
 
      Serial.print( myPin );
      if (myPin == 8 || myPin == 9 || myPin == 10 || myPin == 11 || myPin > 30) {    
           // do nothing
      } else { // OK to analogRead
        
        Serial.print(":" ); 
        Serial.print(analogRead(myPin) );
      }
      Serial.print(", " );
      if (myPin % 20 == 0) {
        Serial.println();
      }
      digitalWrite(LEDB, !digitalRead(LEDB));   // flip LEDB
   }
}
