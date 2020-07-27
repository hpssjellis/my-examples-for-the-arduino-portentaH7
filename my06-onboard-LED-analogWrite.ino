/*
  AnalogWrite for each LED on the Portenta H7

  July 27th, 2020
  by Jeremy Ellis
  Twitter @rocksetta
  Website https://www.rocksetta.com

  
 LED_onboard_analogWrite(LEDB, 0, previousMillisB, ledStateB); Turns the onBoard Blue LED fully off
 LED_onboard_analogWrite(LEDB, 1023, previousMillisB, ledStateB); Turns the onBoard Blue LED fully on

*/

unsigned long previousMillisB;
int ledStateB = HIGH;

unsigned long previousMillisG;
int ledStateG = HIGH;

unsigned long previousMillisR;
int ledStateR = HIGH;

void setup() {
 // pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(LEDB, OUTPUT); 
  pinMode(LEDG, OUTPUT);   // same as LED_BUILTIN
  pinMode(LEDR, OUTPUT); 
}

void loop() {
 LED_onboard_analogWrite(LEDB, 1000, previousMillisB, ledStateB);
 LED_onboard_analogWrite(LEDG, 100, previousMillisG, ledStateG);
 LED_onboard_analogWrite(LEDR, 100, previousMillisR, ledStateR);
}

void LED_onboard_analogWrite(int myPin, int myPWM, unsigned long &myMillis, int &myState){
  unsigned long currentMillis = micros();
  
  if (myPWM > 1023){myPWM = 1023;}
  if (myPWM < 0){myPWM = 0;}
  
  if (myState == LOW){      
     if(currentMillis - myMillis >= myPWM){
        myState = HIGH;
        digitalWrite(myPin, myState);  
        myMillis = currentMillis;
      }     
  } else { 
     if(currentMillis - myMillis >= 1023-myPWM){
        myState = LOW;
        digitalWrite(myPin, myState);    
        myMillis = currentMillis;  
     }
  } 
}
