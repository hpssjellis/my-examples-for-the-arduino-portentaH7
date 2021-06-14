#include "mbed.h"

DigitalInOut pingPin(p5);
Timer t;

int main() {
    pingPin.output();
    wait_us(2);
    pingPin = 1;
    wait_us(5);
    pingPin = 0;
    pingPin.input();
    
    // pulseIn
    t.start();
    while(!pingPin); // wait for high
    int duration = t.read_us();
}
