

byte myIn8bitA, myIn8bitB;
short myIn16bit;
int myHeader, myVerlen, mySpeed, myStartAngle, ......data.......,   myEndAngle, myTimeStamp, myCRC;

// should be an array but this is easier
int myData1,myQuality1, myData2,myQuality2, myData3,myQuality3, myData4,myQuality4, myData5,myQuality5, myData6,myQuality6;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

}

void loop() {
  while (Serial1.available()){

    myIn8bitA = Serial1.read();
    if (myIn8bit == 0x54) {
      //first byte: header
      myHeader = (int) myIn8bitA;  // who cares.
      Serial.println();
      Serial.print("Start: ");
      Serial.print(myIn8bitA, HEX);
      
      // 2nd byte length
      myIn8bitA = Serial1.read();
      myVerlen = (int) myIn8bitA;  // who cares
      Serial.print(" ");
      if (myIn8bitA <= 15 ){Serial.print(" ");} // add a space for single digit hex values
      Serial.print(myIn8bitA, HEX); 

      // 3rd and 4th bytes angular speed iof lidar
      myIn8bitA = Serial1.read();
      myIn8bitB = Serial1.read();
      mySpeed = myIn8bitB *256 + myIn8bitA;   // check the order of this
      Serial.print(" ");
      if (myIn8bitA <= 15 ){Serial.print(" ");} // add a space for single digit hex values
      Serial.print(myIn8bitA, HEX); 
      Serial.print(" ");
      if (myIn8bitB <= 15 ){Serial.print(" ");} // add a space for single digit hex values
      Serial.print(myIn8bitB, HEX); 

      // 5th and 6th bytes start angle
      myIn8bitA = Serial1.read();
      myIn8bitB = Serial1.read();
      myStartAngle = myIn8bitB *256 + myIn8bitA;   // check the order of this
      Serial.print(" ");
      if (myIn8bitA <= 15 ){Serial.print(" ");} // add a space for single digit hex values
      Serial.print(myIn8bitA, HEX); 
      Serial.print(" ");
      if (myIn8bitB <= 15 ){Serial.print(" ");} // add a space for single digit hex values
      Serial.print(myIn8bitB, HEX); 


    // ignore the rest for now.
    // summary of what we have so far
    Serial.println();
    Serial.println("header:"+String(myHeader)+ "verLen:"+String(myVerlen)+ "Speed:"+String(mySpeed)+ "Start Angle:"+String(myStartAngle)   );  
    Serial.println();


  }  // end while

}  // end loop
