 // Testing the PWM pins

void myPwm(int myGPIO, int myDelay){
  
 // digitalWrite(LED_BUILTIN, LOW); 
  for (int x=0; x<=255; x++){
      analogWrite(myGPIO, x);
      delay(myDelay);   
  }
  delay(myDelay);
  for (int x=255; x>=0; x--){
      analogWrite(myGPIO, x);
      delay(myDelay);   
    }
  delay(myDelay);
  
 // digitalWrite(LED_BUILTIN, HIGH); 
}


void setup() {
 
  // pinMode(, OUTPUT);  //PWM9
   //pinMode(9, OUTPUT);  //PWM8 
   pinMode(0, OUTPUT);  //PWM7
   pinMode(1, OUTPUT);  //PWM6
   pinMode(2, OUTPUT);  //PWM5
  // pinMode(3, OUTPUT);  //PWM4   // broken
   pinMode(4, OUTPUT);  //PWM3
   pinMode(5, OUTPUT);  //PWM2
   pinMode(6, OUTPUT);  //PWM1
 //  pinMode(7, OUTPUT);  //PWM0  //Broken
 

    
   pinMode(LEDB, OUTPUT);
   digitalWrite(LEDB, LOW); //Portenta LED on
   delay(2000);
   digitalWrite(LEDB, HIGH); 
   delay(2000);

}

void loop() {

   
   myPwm(0, 1);  
   myPwm(1, 1);  
   myPwm(2, 1);  
 //  myPwm(3, 1);  // broken
   myPwm(4, 1);  
   myPwm(5, 1);  
   myPwm(6, 1);   
  // myPwm(7, 1);  //Broken
  // myPwm(9, 1); 
  // myPwm(9, 1);  
   digitalWrite(LEDB, LOW); //Portenta LED on
   delay(1000);
   digitalWrite(LEDB, HIGH); 
   delay(1000);
   
}
