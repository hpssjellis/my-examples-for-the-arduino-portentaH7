#include "mbed.h"
#include "rtos.h"

using namespace mbed;
using namespace rtos;



DigitalOut myLedRed(PK_5); // red
DigitalOut myLedGreen(PK_6); // green
DigitalOut myLedBlue(PK_7); // blue

Thread thread;

void led2_thread()
{
    while (true) {
        myLedBlue = !myLedBlue;
        ThisThread::sleep_for(1000);
    }
}

int main()
{
    thread.start(led2_thread);

    while (true) {
        //led1 = !led1;
        ThisThread::sleep_for(500);
    }
}
