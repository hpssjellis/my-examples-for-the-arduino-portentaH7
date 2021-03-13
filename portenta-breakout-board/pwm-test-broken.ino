// Testing the PWM pins

void myPwm(int myGPIO, int myDelay){
 
  //pinMode(myGPIO, OUTPUT);  
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
  //pinMode(myGPIO, INPUT); 
   
}


void setup() {

   pinMode(0, OUTPUT);       //PWM6
   pinMode(PWM_2, OUTPUT);       //PWM5
   pinMode(2, OUTPUT);       //PWM4
   //pinMode(3, OUTPUT);     //Broken
   pinMode(4, OUTPUT);       //PWM2
   pinMode(5, OUTPUT);       //PWM1
   pinMode(6, OUTPUT);       //PWM0
   //pinMode(7, OUTPUT);     //Broken
 
   //pinMode(PWM_8, OUTPUT); //PWM6
   //pinMode(PWM_3, OUTPUT); //PWM6
   //pinMode(PH_15, OUTPUT); //Broken

    
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
   // myPwm(3, 1);  // broken
   myPwm(4, 1);  
   myPwm(5, 1);  
   myPwm(6, 1);   
   // myPwm(7, 1);  //Broken
   // myPwm(PWM_3, 1); //nope
   // myPwm(PH_15, 1);  //nope
   digitalWrite(LEDB, LOW); //Portenta LED on
   delay(1000);
   digitalWrite(LEDB, HIGH); 
   delay(1000);
   
}
