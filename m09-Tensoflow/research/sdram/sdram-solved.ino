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
   // How to assign the data directly to the allocated pointer memory
   // without having to make an array as well
   // The following traditional line works
   // sdram_tflite = model_tflite;

   // This line doesn't work
   // sdram_tflite =  {0x54, 0x46, 0x4c, 0x33};



 
   // The following works, but is very clumsy 
   // *(sdram_tflite + 0) =  0x54;
   // *(sdram_tflite + 1) =  0x46;
   // *(sdram_tflite + 2) =  0x4c;
   // *(sdram_tflite + 3) =  0x33;


   // Try this
   // unsigned char buffer[8];
   // memcpy(buffer,"\x20\x38\x00\x00\x0E\x82\x00\x06",8);

   // yes this works fine!
   memcpy(sdram_tflite, "\x54\x46\x4c\x33", model_tflite_len);


   
    
}


void myShowArray( unsigned char b[], int sizeOfArray ) {
   for ( int k = 0 ; k < sizeOfArray ; k++ ){
     Serial.println(b[k], HEX);
   }
   Serial.println();
}


void myShowPointer( unsigned char *b, int sizeOfArray ) {
   for ( int k = 0 ; k < sizeOfArray ; k++ ){
     Serial.println(*(b + k), HEX);
   }
   Serial.println();
}


void loop() {
   Serial.println("Regular array");
   for (int i=0; i < model_tflite_len; i++){
     Serial.println(model_tflite[i], HEX);
   }   
   Serial.println();
   
   Serial.println("SDRAM pointer as an array");
   for (int i=0; i < model_tflite_len; i++){
     Serial.println( *(sdram_tflite + i), HEX );
   }
   Serial.println();
   
   Serial.println("Regular array passed as an array to the receiving function");
   myShowArray(model_tflite, model_tflite_len);

   Serial.println("Pointer passed as a pointer to the receiving function");
   myShowPointer(sdram_tflite, model_tflite_len);
  
   Serial.println("Pointer passed as an array to the receiving function");
  // myShowArray(*&sdram_tflite, model_tflite_len);
   myShowArray(sdram_tflite, model_tflite_len);
   
   Serial.println("--------------------");
   Serial.println();  
   delay(4000);
}
