
#define FREQUENCY_HZ        50
#define INTERVAL_MS         (1000 / (FREQUENCY_HZ + 1))

void setup() {
   Serial.begin(115200);
   Serial.println("Started");
   randomSeed(analogRead(A0));
   //while (!Serial) {;  } 
   pinMode(LEDR, OUTPUT);
   pinMode(LEDG, OUTPUT);
   pinMode(LEDB, OUTPUT);
   

// To turn off to begin with   
   digitalWrite(LEDB, HIGH);
   digitalWrite(LEDG, HIGH);
   digitalWrite(LEDR, HIGH);

   

}

void loop() {
    static unsigned long last_interval_ms = 0;
    
    int myIn1 = rand() % 2;  // either 0 or 1
    int myIn2 = rand() % 2;  // I would do a for loop but this was easy.
    int myIn3 = rand() % 2;
    int myIn4 = rand() % 2;
    int myIn5 = rand() % 2;
    int myIn6 = rand() % 2;
    int myIn7 = rand() % 2;
    int myIn8 = rand() % 2;
    int myInput[] = { myIn1, myIn2, myIn3, myIn4, myIn5, myIn6, myIn7, myIn8 };   // 8 inputs.
 
   // float myOutput[4];   // 4 output floats
    int myOutput[4];   // 4 output floats, but using ints for this
  
    myOutput[0] = rand() % 2;
    myOutput[1] = rand() % 2;
    myOutput[2] = rand() % 2;
    myOutput[3] = rand() % 2;
      


// Canned reponse
// To test the model

// If the first 3 inputs are 1 then make only the first output 1
if (myInput[0] == 1 && myInput[1] == 1 && myInput[2] == 1){ 
    myOutput[0] = 1;
    myOutput[1] = 0;
    myOutput[2] = 0;
    myOutput[3] = 0; 
  }



// If the last 3 inputs are 1 then make only the last output 1
if (myInput[5] == 1 && myInput[6] == 1 && myInput[7] == 1){ 
    myOutput[0] = 0;
    myOutput[1] = 0;
    myOutput[2] = 0;
    myOutput[3] = 1; 
  }


/*

   // Now just print the csv file in good format   

   Serial.print(String(myInput[0]) +  String(myInput[1]) +  String(myInput[2]) +  String(myInput[3]) +  String(myInput[4]) + String(myInput[5]) +  String(myInput[6]) + String(myInput[7]) ); 
   Serial.println(", " + String(myOutput[0]) + String(myOutput[1]) + String(myOutput[2]) + String(myOutput[3]) );
     

*/
    

    digitalWrite(LEDB, HIGH); // turn Blue LED off
    
    if (millis() > last_interval_ms + INTERVAL_MS) {
        last_interval_ms = millis();
        digitalWrite(LEDB, LOW);    // Blue LED on

        Serial.print(myInput[0]);
        Serial.print(myInput[1]);
        Serial.print(myInput[2]);
        Serial.print(myInput[3]);
        Serial.print(myInput[4]);
        Serial.print(myInput[5]);
        Serial.print(myInput[6]);
        Serial.print(myInput[7]);
        Serial.print('\t');            // tab
        Serial.print(myOutput[0]);
        Serial.print(myOutput[1]);
        Serial.print(myOutput[2]);
        Serial.println(myOutput[3]);
    }
}
















