

 

//T4A01-RangeFinder-Name.ino 
//using Ultrasonic Range Finder from Robotshop 

// https://www.robotshop.com/en/hc-sr04-ultrasonic-range-finder-tys.html

  

unsigned long duration; 

  

void setup() { 
  Serial.begin(115200);

    pinMode(LEDG, OUTPUT);   // LED_BUILTIN, LEDB, LEDR, LEDG
    pinMode(LEDB, OUTPUT);   
    
 // ultrasonic range finder Robotshop RB-lte-54 pin settings 
                           // GND pin goes to ground  (GND)
    pinMode(D5, INPUT);    // echo 
    pinMode(D6, OUTPUT);   // Trig 
                           // 3V3 pin on the Portenta Can use +5V pin as well

} 

void loop(){ 

        delay(10);                      // even cicuits need a break 
        digitalWrite(D5, HIGH);         // activate trigger 
        delayMicroseconds(10); 
        digitalWrite(D5, LOW);          // de-activate trigger 

        duration = pulseIn(D6, HIGH, 10);   // how long until a reply? 
                                        // a blocking call so may wait a few seconds 

        if (duration > 600    ){        // Change this value!!!!!
                                        // raw data from 200 to 16000                                          
                                        // where  2000 raw = ~35cm,  4000 raw = ~80cm                                    
            digitalWrite(LEDB, LOW);     // blue if far
            digitalWrite(LEDG, HIGH);
            Serial.println();
            Serial.println("Far");
        } else { 
            digitalWrite(LEDB, HIGH); 
            digitalWrite(LEDG, LOW);      // green if close
            Serial.print(".");
        }  

}
