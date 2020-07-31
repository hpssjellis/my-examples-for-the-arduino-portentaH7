


/*
  AnalogWrite for each on-board LED using the Portenta H7
  This is needed since the onboard LED's are reverse set for LOW and HIGH to protect the board

  July 27th, 2020
  by Jeremy Ellis
  Twitter @rocksetta
  Website https://www.rocksetta.com

  RGB idea by Daniel Danaie

  example usage
  LED_onboard_setRGB(255, 0, 0);  // set LED to red

  or
  
  LED_onboard_analogWrite(LEDB, 0, previousMillisB, ledStateB); Turns the onBoard Blue LED fully off
  LED_onboard_analogWrite(LEDB, 255, previousMillisB, ledStateB); Turns the onBoard Blue LED fully on

  Note because of the sensitive timer used you can not use this code with delay(1000);

*/



unsigned long myTimer = millis();


// These variable must be global

unsigned long previousMillisR;
int ledStateR = HIGH;
int myAmountR;

unsigned long previousMillisG;
int ledStateG = HIGH;
int myAmountG;

unsigned long previousMillisB;
int ledStateB = HIGH;
int myAmountB;
  
  

  

void setup() {
  Serial.begin(9600);
  pinMode(LEDB, OUTPUT); 
  pinMode(LEDG, OUTPUT);   // same as LED_BUILTIN
  pinMode(LEDR, OUTPUT); 
  randomSeed(analogRead(A0));
}

void loop() {
  unsigned long myNow = millis();
  // LED_onboard_setRGB(25, 25, 255); // example blue

  if (myNow - myTimer >= 1000){   // color change delay 1000 = 1 second
     myTimer = myNow;
     myAmountR =  rand()% 256;
     myAmountG =  rand()% 256;
     myAmountB =  rand()% 256;   
     Serial.println("Red:"+String(myAmountR) + ", Green:"+ String(myAmountG) + ", Blue:"+ String(myAmountB));
  }
  LED_onboard_setRGB( myAmountR, myAmountG, myAmountB);
}


void LED_onboard_setRGB(int colorR, int colorG, int colorB){

   LED_onboard_analogWrite(LEDR, colorR, previousMillisR, ledStateR);
   LED_onboard_analogWrite(LEDG, colorG, previousMillisG, ledStateG);
   LED_onboard_analogWrite(LEDB, colorB, previousMillisB, ledStateB);
}

void LED_onboard_analogWrite(int myPin, int myPWM, unsigned long &myMillis, int &myState){
  unsigned long currentMillis = micros();
  
  if (myPWM > 255){myPWM = 255;}
  if (myPWM < 0){myPWM = 0;}
  
  if (myState == LOW){      
     if(currentMillis - myMillis >= myPWM){
        myState = HIGH;
        digitalWrite(myPin, myState);  
        myMillis = currentMillis;
      }     
  } else { 
     if(currentMillis - myMillis >= 255-myPWM){
        myState = LOW;
        digitalWrite(myPin, myState);    
        myMillis = currentMillis;  
     }
  } 
}
