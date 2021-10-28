
#include <SDRAM.h>

#define ALIGN_PTR(p,a)   ((p & (a-1)) ?(((uintptr_t)p + a) & ~(uintptr_t)(a-1)) : p)

SDRAMClass mySDRAM;

uint8_t *sdram_frame_buffer; // 32-byte aligned
static uint8_t *ei_camera_frame_mem;

const unsigned char model_tflite[] = {0x54, 0x46, 0x4c, 0x33};
unsigned int model_tflite_len = 4;




void setup() {
  Serial.begin(115200);
  mySDRAM.begin(SDRAM_START_ADDRESS);   // for camera 320x320
  
   ei_camera_frame_mem = (uint8_t *) SDRAM.malloc(4 + 32 /*alignment*/);
   sdram_frame_buffer = (uint8_t *)ALIGN_PTR((uintptr_t)ei_camera_frame_mem, 32);

   

   
}

void loop() {
  Serial.println("Regular Array");
   for (int i=0; i < model_tflite_len; i++){
     Serial.println(model_tflite[i]);
   }   
   
  Serial.println("SDRAM pointer as an array");
   for (int i=0; i < model_tflite_len; i++){
     Serial.println( "-" );
    // Serial.println( *(sdram_frame_buffer + i) );
   }
   delay(2000);
}
