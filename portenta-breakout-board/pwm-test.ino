 // Testing the PWM pins

void myPwm(int myGPIO, int myDelay){
  pinMode(myGPIO, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); //Portenta LED on
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
  digitalWrite(LED_BUILTIN, HIGH); 
}


void setup() {
  
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, LOW); //Portenta LED on
   delay(2000);
   digitalWrite(LED_BUILTIN, HIGH); 
   delay(2000);

}

void loop() {
  
   myPwm(A3, 1);  //GPIO, delay time (m/s)
   myPwm(A4, 1);   
   myPwm(A5, 1);   
   //delay(1000);
   
}
