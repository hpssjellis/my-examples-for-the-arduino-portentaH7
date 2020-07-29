/*  Blink, AnalogRead and Serial
 *  Arduino Portenta Analog test program 
 *
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update July 29th, 2020
 * 
 */

void setup(){  
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  // while (!Serial);  // Please don't do this it messes up beginners
  
}

void loop() {


  Serial.println("A0 Analog Read max = 1023, Actual Value: "+String(analogRead(A0)) );
  Serial.println("A1 Analog Read max = 1023, Actual Value: "+String(analogRead(A1)) );
  Serial.println("A2 Analog Read max = 1023, Actual Value: "+String(analogRead(A2)) );
  Serial.println("A3 Analog Read max = 1023, Actual Value: "+String(analogRead(A3)) );
  Serial.println("A4 Analog Read max = 1023, Actual Value: "+String(analogRead(A4)) );
  Serial.println("A5 Analog Read max = 1023, Actual Value: "+String(analogRead(A5)) );
  Serial.println("A6 Analog Read max = 1023, Actual Value: "+String(analogRead(A6)) );
  Serial.println("-------------------------------------------------------------------");
  Serial.println();

  // Flash LED 3 times
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);                      
  digitalWrite(LED_BUILTIN, HIGH);    
  delay(100);                    

  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);                      
  digitalWrite(LED_BUILTIN, HIGH);    
  delay(100);      
                
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);                      
  digitalWrite(LED_BUILTIN, HIGH);    
  delay(3000);    // longer wait 
                  
}
