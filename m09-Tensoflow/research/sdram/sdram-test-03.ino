// Needed for SDRAM assignment on Arduino Portenta
#include <SDRAM.h>
#define ALIGN_PTR(p,a)   ((p & (a-1)) ?(((uintptr_t)p + a) & ~(uintptr_t)(a-1)) : p)
SDRAMClass mySDRAM;



// assign values to a regular array
unsigned char model_tflite[] = {0x54, 0x46, 0x4c, 0x33};
unsigned int model_tflite_len = 4;



// define SDRAM pointer
unsigned char *sdram_mem;
unsigned char *sdram_tflite; // 32-byte aligned




void setup() {
   Serial.begin(115200);
   mySDRAM.begin(SDRAM_START_ADDRESS);   

   // setup SDRAM memory block
   sdram_mem = (unsigned char *) SDRAM.malloc(4 + 32 /*alignment*/);
   sdram_tflite = (unsigned char *)ALIGN_PTR((uintptr_t)sdram_mem, 32);

   // THE PROBLEM
   // How to assign the data directly to the allocated memory
   // without having to make the actual array
   // The following line works
   // sdram_tflite = model_tflite;

   // This line doesn't work
   // sdram_tflite =  {0x54, 0x46, 0x4c, 0x33};
 
   // The following works, but is very clumsy 
   *(sdram_tflite + 0) =  0x54;
   *(sdram_tflite + 1) =  0x46;
   *(sdram_tflite + 2) =  0x4c;
   *(sdram_tflite + 3) =  0x33;
   
   
}

void loop() {
  Serial.println("Regular Array");
   for (int i=0; i < model_tflite_len; i++){
     Serial.println(model_tflite[i], HEX);
   }   
   
  Serial.println("SDRAM pointer as an array");
   for (int i=0; i < model_tflite_len; i++){
     //Serial.println( "-" );
     Serial.println( *(sdram_tflite + i), HEX );
   }
   Serial.println("--------------------");
   Serial.println();
   delay(4000);
}
