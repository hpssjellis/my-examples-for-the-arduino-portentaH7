
void setup() {
   randomSeed(analogRead(A0));
   Serial.begin(9600);   
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
   } 
   pinMode(LEDR, OUTPUT);
   pinMode(LEDG, OUTPUT);
   pinMode(LEDB, OUTPUT);

// To turn off to begin with   
   digitalWrite(LEDB, HIGH);
   digitalWrite(LEDG, HIGH);
   digitalWrite(LEDR, HIGH);
   //csv file headers
   Serial.println("Input, Labels");
  
}


void loop() {

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


   // Now just print the csv file in good format   

   Serial.print(String(myInput[0]) +  String(myInput[1]) +  String(myInput[2]) +  String(myInput[3]) +  String(myInput[4]) + String(myInput[5]) +  String(myInput[6]) + String(myInput[7]) ); 
   Serial.println(", " + String(myOutput[0]) + String(myOutput[1]) + String(myOutput[2]) + String(myOutput[3]) );
     
   //  Serial.print("All 8 inputs: " +  String(myInput[0])+  String(myInput[1])+  String(myInput[2])+  String(myInput[3])+  String(myInput[4])+ String(myInput[5])+  String(myInput[6])+  String(myInput[7]) ); 
 //  Serial.print("The 4 predictions, Red: " + String(myOutput[0],4) + ", Green: " + String(myOutput[1],4) + ", Blue: " + String(myOutput[2],4) );
    

    digitalWrite(LEDB, LOW);
    delay(100); // slows things down  
    digitalWrite(LEDB, HIGH);
    delay(100); // slows things down  
}
