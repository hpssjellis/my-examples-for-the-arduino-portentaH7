
Form

https://github.com/arduino/ArduinoCore-mbed/issues/364



Pin 4 and 5 on the MKR connector (PC_7 / PC_6 using STM32 naming) are mapped to USART6, 
while PA_8 (pin 6) is UART7 RX. You can enable the first one using this code




UART mySecondSerialOnMKRHeaders(PC_6, PC_7, NC, NC);
void setup() {
  mySecondSerialOnMKRHeaders.begin(115200);
}

void loop() {
  mySecondSerialOnMKRHeaders.println("mySecondSerialOnMKRHeaders");
}
while the second one is a bit useless (unless you only need to receive data) but you can declare it as

UART myThirdRXOnlySerialOnMKRHeaders(NC, PA_8, NC, NC);
