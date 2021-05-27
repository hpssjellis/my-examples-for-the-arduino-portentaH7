/*
 * To comunicate from the murata to the Portenta
 * For after the murata LoRa has been programmed using a linux machine
 * 
 * Can be ran normal or from double button push bootloader and from windows arduino IDE
 *
*/


#include <Arduino.h>

int  myCount=48;  //48 = ascii 0,    58 ascii 9

UART myUART3(PJ_8,  PJ_9,  NC, NC); //TX, TR, RTS, CTS  NOTE: NC means not connected

void setup(){
    pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 
    Serial.begin(115200);
    myUART3.begin(9600);   // not 115200 does not work on Murata module

}

void loop(){
   myCount++;
   if (myCount >= 58){myCount = 48;}   //48 = ascii 0,    58 ascii 9
   digitalWrite(LEDB, !digitalRead(LEDB));   //switch on / off
   char x = (char)myCount;  //random(48, 57);  // ascii code for numbers 0 to 9
   myUART3.write(x); 
   delay(3);  // start at 100 and check the order. mine messes up at 2 ms
     
}
