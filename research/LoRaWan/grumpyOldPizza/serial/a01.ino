#include "TimerMillis.h"
#include "LoRaRadio.h"
///#include "Uart.h"
//#include "HardwareSerial.h"

TimerMillis timerOff;
TimerMillis timerOn;

//Uart mySerialSTM32LO(STM_TX1,  STM_RX1,  NC, NC);  // murata modem,   TX, RX, RTS, CTS  NOTE: NC means not connected

//Note: Serial and Serial1 work

void callbackOff(void){
}

void callbackOn(void){
    Serial1.write("J");
    timerOff.start(callbackOff, 250);
}

void setup( void ){
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 0);
    Serial1.begin(9600);
    
    timerOn.start(callbackOn, 0, 2000);
}

void loop( void ){
}
