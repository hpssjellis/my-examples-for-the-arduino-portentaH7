/*  Blink, AnalogRead and Serial
 *  Arduino test program 
 *
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update July 25th, 2020
 * 
 */

void setup(){  
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  // while (!Serial);  // Please don't do this it messes up beginners
  
}

void loop() {

  int sensorValue = analogRead(A0);
  Serial.print("A0 Analog Read max = 1023, Actual Value: ");
  Serial.println(sensorValue);

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
