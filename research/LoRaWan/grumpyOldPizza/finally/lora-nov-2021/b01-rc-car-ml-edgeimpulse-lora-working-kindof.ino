/*
 * 
 * Must use portenta with Vision camerera and Grove OLED 
 * Should be implemented with MBED version greater than 1.4.2
 * Until then needs the 2 main library folders Portenta_Camera and Himax_HM01B0
 * 
 * 
 *
 * Purchase here https://wiki.seeedstudio.com/Grove-OLED_Display_0.96inch/ about $20 USD
 *
 * Note u8g2 is an arduino search caplble library, easy to install
 *
 *  using 128 x 64 seeeduino OLED
 *  black GND 
 *  red 3v3      so do not need the protective resistors below
 *  white SDA    D11 // on portenta
 *  yellow SCL   D12 // on portenta
 *
 * another reference here 
 * https://github.com/olikraus/u8g2/wiki/u8g2reference#setfont
 *
 */

 /*
 * 
 * Must use portenta with Vision camerera and Grove OLED 
 * Should be implemented with MBED version greater than 1.4.2
 * Until then needs the 2 main library folders Portenta_Camera and Himax_HM01B0
 * 
 * 
 *
 * Purchase here https://www.waveshare.com/1.5inch-OLED-Module.htm about $29 USD
 *
 * Note u8g2 is an arduino search caplble library, easy to install
 *
 *  using 128 x 64 seeeduino OLED
 *  black GND 
 *  red 3v3      so do not need the protective resistors below
 *  //white SDA    D11 // on portenta
 *  //yellow SCL   D12 // on portenta
 *  
 *  FOR the GRAYSCALE Waveshare OLED
 *   blue  DIN (mosi) D8
 *   yellow (sck) D9 
 *   orange (cs) D7
 *   green (dc)  D6
 *   white (reset) not needed but D14 if you did
 *
 * another reference here 
 * https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
 *
 */
 
#include <Arduino.h>  // only needed for https://platformio.org/
#include <SDRAM.h>
#include <Adafruit_SSD1327.h>

// Used for software SPI
#define OLED_CLK D9  //yellow wire
#define OLED_MOSI D8 // blue wire 

// Used for software or hardware SPI
#define OLED_CS D7  // orange wire
#define OLED_DC D6   // green wire 

// Used for I2C or SPI
#define OLED_RESET -1

// hardware SPI
Adafruit_SSD1327 display(128, 128, &SPI, OLED_DC, OLED_RESET, OLED_CS);




// works
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   //(rotation, clock, data [, reset])


#define EI_DSP_IMAGE_BUFFER_STATIC_SIZE 128


/* Includes ---------------------------------------------------------------- */

#include <ei-portenta-42-try-96x96-gray-better-trained_inferencing.h>

//#include <ei-0unknown-1popGoRight-2waterGoLeft-3fast-v0-1-2_inferencing.h>

//#include <ei-0unknown-1popGoRight-2waterGoLeft-3fast-v0-1-1_inferencing.h>
//#include <ei-0unknown-1popGoRight-2waterGoLeft-3fast-v0-0-3_inferencing.h>


// just to test
//#include <ei-portenta-42-try-96x96-gray-better-trained_inferencing.h>



//#include <ei-portenta-42-try-96x96-gray-better-trained_inferencing.h>




#include "camera.h"

CameraClass myCam;


// raw frame buffer from the camera
#define FRAME_BUFFER_COLS          320   // 160
#define FRAME_BUFFER_ROWS          320   //240   // 120

//uint16_t frame_buffer[FRAME_BUFFER_COLS * FRAME_BUFFER_ROWS] = { 0 };

//uint8_t frame_buffer[320*240] __attribute__((aligned(32)));

#define ALIGN_PTR(p,a)   ((p & (a-1)) ?(((uintptr_t)p + a) & ~(uintptr_t)(a-1)) : p)


SDRAMClass mySDRAM;

uint8_t *ei_camera_frame_buffer; // 32-byte aligned
static uint8_t *ei_camera_frame_mem;



// cutout that we want (this does not do a resize, which would also be an option, but you'll need some resize lib for that)
#define CUTOUT_COLS                 EI_CLASSIFIER_INPUT_WIDTH
#define CUTOUT_ROWS                 EI_CLASSIFIER_INPUT_HEIGHT
const int cutout_row_start = (FRAME_BUFFER_ROWS - CUTOUT_ROWS) / 2;
const int cutout_col_start = (FRAME_BUFFER_COLS - CUTOUT_COLS) / 2;

int x1Map, x2Map, y1Map, y2Map;
//String myMessage01, myMessage02;
//int myClass0Count=0;
//int myClass1Count=0;
//int myClass2Count=0;
//int myClass3Count=0;
int myClassCount[EI_CLASSIFIER_LABEL_COUNT];


void print_memory_info() {
    // allocate enough room for every thread's stack statistics
    int cnt = osThreadGetCount();
    mbed_stats_stack_t *stats = (mbed_stats_stack_t*) malloc(cnt * sizeof(mbed_stats_stack_t));
 
    cnt = mbed_stats_stack_get_each(stats, cnt);
    for (int i = 0; i < cnt; i++) {
        ei_printf("Thread: 0x%lX, Stack size: %lu / %lu\r\n", stats[i].thread_id, stats[i].max_size, stats[i].reserved_size);
    }
    free(stats);
 
    // Grab the heap statistics
    mbed_stats_heap_t heap_stats;
    mbed_stats_heap_get(&heap_stats);
    ei_printf("Heap size: %lu / %lu bytes\r\n", heap_stats.current_size, heap_stats.reserved_size);
}




/**
*  supplied by Raul Edge Impulse
*
*/
// This include file works in the Arduino environment
// to define the Cortex-M intrinsics
#ifdef __ARM_FEATURE_SIMD32
#include <device.h>
#endif
// This needs to be < 16 or it won't fit. Cortex-M4 only has SIMD for signed multiplies
#define FRAC_BITS 14
#define FRAC_VAL (1<<FRAC_BITS)
#define FRAC_MASK (FRAC_VAL - 1)

// Resize
//
// Assumes that the destination buffer is dword-aligned
// Can be used to resize the image smaller or larger
// If resizing much smaller than 1/3 size, then a more rubust algorithm should average all of the pixels
// This algorithm uses bilinear interpolation - averages a 2x2 region to generate each new pixel
//
// Optimized for 32-bit MCUs
// supports 8 and 16-bit pixels
void resizeImage(int srcWidth, int srcHeight, uint8_t *srcImage, int dstWidth, int dstHeight, uint8_t *dstImage, int iBpp)
{
    uint32_t src_x_accum, src_y_accum; // accumulators and fractions for scaling the image
    uint32_t x_frac, nx_frac, y_frac, ny_frac;
    int x, y, ty, tx;

    if (iBpp != 8 && iBpp != 16)
        return;
    src_y_accum = FRAC_VAL/2; // start at 1/2 pixel in to account for integer downsampling which might miss pixels
    const uint32_t src_x_frac = (srcWidth * FRAC_VAL) / dstWidth;
    const uint32_t src_y_frac = (srcHeight * FRAC_VAL) / dstHeight;
    const uint32_t r_mask = 0xf800f800;
    const uint32_t g_mask = 0x07e007e0;
    const uint32_t b_mask = 0x001f001f;
    uint8_t *s, *d;
    uint16_t *s16, *d16;
    uint32_t x_frac2, y_frac2; // for 16-bit SIMD
    for (y=0; y < dstHeight; y++) {
        ty = src_y_accum >> FRAC_BITS; // src y
        y_frac = src_y_accum & FRAC_MASK;
        src_y_accum += src_y_frac;
        ny_frac = FRAC_VAL - y_frac; // y fraction and 1.0 - y fraction
        y_frac2 = ny_frac | (y_frac << 16); // for M4/M4 SIMD
        s = &srcImage[ty * srcWidth];
        s16 = (uint16_t *)&srcImage[ty * srcWidth * 2];
        d = &dstImage[y * dstWidth];
        d16 = (uint16_t *)&dstImage[y * dstWidth * 2];
        src_x_accum = FRAC_VAL/2; // start at 1/2 pixel in to account for integer downsampling which might miss pixels
        if (iBpp == 8) {
        for (x=0; x < dstWidth; x++) {
            uint32_t tx, p00,p01,p10,p11;
            tx = src_x_accum >> FRAC_BITS;
            x_frac = src_x_accum & FRAC_MASK;
            nx_frac = FRAC_VAL - x_frac; // x fraction and 1.0 - x fraction
            x_frac2 = nx_frac | (x_frac << 16);
            src_x_accum += src_x_frac;
            p00 = s[tx]; p10 = s[tx+1];
            p01 = s[tx+srcWidth]; p11 = s[tx+srcWidth+1];
    #ifdef __ARM_FEATURE_SIMD32
            p00 = __SMLAD(p00 | (p10<<16), x_frac2, FRAC_VAL/2) >> FRAC_BITS; // top line
            p01 = __SMLAD(p01 | (p11<<16), x_frac2, FRAC_VAL/2) >> FRAC_BITS; // bottom line
            p00 = __SMLAD(p00 | (p01<<16), y_frac2, FRAC_VAL/2) >> FRAC_BITS; // combine
    #else // generic C code
            p00 = ((p00 * nx_frac) + (p10 * x_frac) + FRAC_VAL/2) >> FRAC_BITS; // top line
            p01 = ((p01 * nx_frac) + (p11 * x_frac) + FRAC_VAL/2) >> FRAC_BITS; // bottom line
            p00 = ((p00 * ny_frac) + (p01 * y_frac) + FRAC_VAL/2) >> FRAC_BITS; // combine top + bottom
    #endif // Cortex-M4/M7
            *d++ = (uint8_t)p00; // store new pixel
        } // for x
        } // 8-bpp
        else
        { // RGB565
        for (x=0; x < dstWidth; x++) {
            uint32_t tx, p00,p01,p10,p11;
            uint32_t r00, r01, r10, r11, g00, g01, g10, g11, b00, b01, b10, b11;
            tx = src_x_accum >> FRAC_BITS;
            x_frac = src_x_accum & FRAC_MASK;
            nx_frac = FRAC_VAL - x_frac; // x fraction and 1.0 - x fraction
            x_frac2 = nx_frac | (x_frac << 16);
            src_x_accum += src_x_frac;
            p00 = __builtin_bswap16(s16[tx]); p10 = __builtin_bswap16(s16[tx+1]);
            p01 = __builtin_bswap16(s16[tx+srcWidth]); p11 = __builtin_bswap16(s16[tx+srcWidth+1]);
    #ifdef __ARM_FEATURE_SIMD32
            {
            p00 |= (p10 << 16);
            p01 |= (p11 << 16);
            r00 = (p00 & r_mask) >> 1; g00 = p00 & g_mask; b00 = p00 & b_mask;
            r01 = (p01 & r_mask) >> 1; g01 = p01 & g_mask; b01 = p01 & b_mask;
            r00 = __SMLAD(r00, x_frac2, FRAC_VAL/2) >> FRAC_BITS; // top line
            r01 = __SMLAD(r01, x_frac2, FRAC_VAL/2) >> FRAC_BITS; // bottom line
            r00 = __SMLAD(r00 | (r01<<16), y_frac2, FRAC_VAL/2) >> FRAC_BITS; // combine
            g00 = __SMLAD(g00, x_frac2, FRAC_VAL/2) >> FRAC_BITS; // top line
            g01 = __SMLAD(g01, x_frac2, FRAC_VAL/2) >> FRAC_BITS; // bottom line
            g00 = __SMLAD(g00 | (g01<<16), y_frac2, FRAC_VAL/2) >> FRAC_BITS; // combine
            b00 = __SMLAD(b00, x_frac2, FRAC_VAL/2) >> FRAC_BITS; // top line
            b01 = __SMLAD(b01, x_frac2, FRAC_VAL/2) >> FRAC_BITS; // bottom line
            b00 = __SMLAD(b00 | (b01<<16), y_frac2, FRAC_VAL/2) >> FRAC_BITS; // combine
            }
    #else // generic C code
            {
            r00 = (p00 & r_mask) >> 1; g00 = p00 & g_mask; b00 = p00 & b_mask;
            r10 = (p10 & r_mask) >> 1; g10 = p10 & g_mask; b10 = p10 & b_mask;
            r01 = (p01 & r_mask) >> 1; g01 = p01 & g_mask; b01 = p01 & b_mask;
            r11 = (p11 & r_mask) >> 1; g11 = p11 & g_mask; b11 = p11 & b_mask;
            r00 = ((r00 * nx_frac) + (r10 * x_frac) + FRAC_VAL/2) >> FRAC_BITS; // top line
            r01 = ((r01 * nx_frac) + (r11 * x_frac) + FRAC_VAL/2) >> FRAC_BITS; // bottom line
            r00 = ((r00 * ny_frac) + (r01 * y_frac) + FRAC_VAL/2) >> FRAC_BITS; // combine top + bottom
            g00 = ((g00 * nx_frac) + (g10 * x_frac) + FRAC_VAL/2) >> FRAC_BITS; // top line
            g01 = ((g01 * nx_frac) + (g11 * x_frac) + FRAC_VAL/2) >> FRAC_BITS; // bottom line
            g00 = ((g00 * ny_frac) + (g01 * y_frac) + FRAC_VAL/2) >> FRAC_BITS; // combine top + bottom
            b00 = ((b00 * nx_frac) + (b10 * x_frac) + FRAC_VAL/2) >> FRAC_BITS; // top line
            b01 = ((b01 * nx_frac) + (b11 * x_frac) + FRAC_VAL/2) >> FRAC_BITS; // bottom line
            b00 = ((b00 * ny_frac) + (b01 * y_frac) + FRAC_VAL/2) >> FRAC_BITS; // combine top + bottom
            }
    #endif // Cortex-M4/M7
            r00 = (r00 << 1) & r_mask;
            g00 = g00 & g_mask;
            b00 = b00 & b_mask;
            p00 = (r00 | g00 | b00); // re-combine color components
            *d16++ = (uint16_t)__builtin_bswap16(p00); // store new pixel
        } // for x
        } // 16-bpp
    } // for y
} /* resizeImage() */





static inline void mono_to_rgb(uint8_t mono_data, uint8_t *r, uint8_t *g, uint8_t *b) {
    uint8_t v = mono_data;
    *r = *g = *b = v;
}

int ei_camera_cutout_get_data(size_t offset, size_t length, float *out_ptr) {
    size_t bytes_left = length;
    size_t out_ptr_ix = 0;

    // read byte for byte
    while (bytes_left != 0) {

        // grab the value and convert to r/g/b
        uint8_t pixel = ei_camera_frame_buffer[offset];

        uint8_t r, g, b;
        mono_to_rgb(pixel, &r, &g, &b);

        // then convert to out_ptr format
        float pixel_f = (r << 16) + (g << 8) + b;
        out_ptr[out_ptr_ix] = pixel_f;

        // and go to the next pixel
        out_ptr_ix++;
        offset++;
        bytes_left--;
    }

    // and done!
    return 0;
}





/**
 * @brief      Arduino setup function
 */
void setup()
{

SerialLoRa.begin(9600);

  
  mySDRAM.begin(SDRAM_START_ADDRESS);   // for camera 320x320



 // ei_camera_frame_buffer = (uint8_t *)mySDRAM.malloc(320 * 320 * sizeof(uint8_t));
 ////uint8_t frame_buffer[320*240] __attribute__((aligned(32)));



    ei_camera_frame_mem = (uint8_t *) SDRAM.malloc(320 * 320 + 32 /*alignment*/);
    ei_camera_frame_buffer = (uint8_t *)ALIGN_PTR((uintptr_t)ei_camera_frame_mem, 32);

  
   if ( ! display.begin(0x3D) ) {   // start Grayscale OLED
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }    
    display.setTextSize(1);
    display.setTextColor(SSD1327_WHITE);

    display.setRotation(0);
    display.setCursor(0,0);
  // put your setup code here, to run once:

   // int x1 = (int)cutout_col_start;
   // int x2 = (int)CUTOUT_COLS;
   // int y1 = (int)cutout_row_start;  
   // int y2 = (int)CUTOUT_ROWS; 

    //   map cutout of the 320 x 320   // 240 model to OLED 128 x 64 screen
    x1Map = map((int)cutout_col_start, 0, 320, 0, 127);  
    x2Map = map((int)CUTOUT_COLS, 0, 320, 0, 127);
    y1Map = map((int)cutout_row_start, 0, 320, 0, 127);
    y2Map = map((int)CUTOUT_ROWS, 0, 320, 0, 127);

    Serial.begin(115200);
     
    pinMode(LEDR, OUTPUT); 
    pinMode(LEDG, OUTPUT);   
    pinMode(LEDB, OUTPUT);  
      

    // Init the cam
    myCam.begin(CAMERA_R320x320, 30);

   // Serial.println("Edge Impulse Inferencing Demo");
}

/**
 * @brief      Arduino main function
 */
void loop()
{

    display.clearDisplay();                 // clear the internal memory

       
   // ei_printf("Edge Impulse standalone inferencing (Arduino)\n");
   // ei_printf("CUTOUT_COLS : %d\n", CUTOUT_COLS );
   // ei_printf("CUTOUT_ROWS : %d\n", CUTOUT_ROWS );
   // ei_printf("FRAME_BUFFER_COLS : %d\n", FRAME_BUFFER_COLS );
   // ei_printf("FRAME_BUFFER_ROWS : %d\n", FRAME_BUFFER_ROWS );
   // ei_printf("sizeof(ei_camera_frame_buffer) : %d\n", sizeof(&ei_camera_frame_buffer) );
   // print_memory_info();



 Serial.println();

      for (int x=0; x < FRAME_BUFFER_COLS; x++){     // FRAME_BUFFER_COLS = 320
        for (int y=0; y < FRAME_BUFFER_ROWS; y++){       //FRAME_BUFFER_ROWS = 320   //240
          //frame_buffer[FRAME_BUFFER_COLS * FRAME_BUFFER_ROWS]
          
          uint8_t myGRAY = ei_camera_frame_buffer[(y * (int)FRAME_BUFFER_COLS) + x];  
         // if (myGRAY > 100){  // if brightish then put pixel on OLED 0 to 255

            int myGrayMap = map(myGRAY, 0, 255, 0, 15);  
            int xMap = map(x, 0, 320, 0, 127);
            int yMap = map(y, 0, 320, 0, 127);
           display.drawPixel(xMap, yMap, myGrayMap );   // grayscale 0-255, 128x128  //128 x 64
          //}
      } 
   }

    //display.drawRect(x1Map, y1Map,   x2Map, y2Map, SSD1327_WHITE );
    display.drawRect(2, 2,   126, 126, SSD1327_WHITE );  // rectangle around outside of OLED

    display.setCursor(20,10);
    display.println("Rocksetta");

    




    

    ei_impulse_result_t result = { 0 };
     
   int myCamResult =  myCam.grab(ei_camera_frame_buffer); // myCamResult should be zero 

 
 
    resizeImage(320, 320, // <-- input buf resolution
            ei_camera_frame_buffer, // <-- input buf
            96, 96, // output buf resolutions
            ei_camera_frame_buffer, // <-- output buf can be the same
            8); // <-- bits per pixel
 
    ei::signal_t signal;
    signal.total_length = 96 * 96; // <-- in pixels 
    signal.get_data = &ei_camera_cutout_get_data;
 
 
 
 
 
 
    // the features are stored into flash, and we don't want to load everything into RAM
   // signal_t features_signal;
   // features_signal.total_length = CUTOUT_COLS * CUTOUT_ROWS;
   // features_signal.get_data = &cutout_get_data;

    // invoke the impulse
    EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false /* debug */);
    ei_printf("run_classifier returned: %d\n", res);

    if (res != 0) return;

    // print the predictions
    ei_printf("Predictions ");
    ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
        result.timing.dsp, result.timing.classification, result.timing.anomaly);
    ei_printf(": \n");
    ei_printf("[");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_printf("%.5f", result.classification[ix].value);
#if EI_CLASSIFIER_HAS_ANOMALY == 1
        ei_printf(", ");
#else
        if (ix != EI_CLASSIFIER_LABEL_COUNT - 1) {
            ei_printf(", ");
        }
#endif
    }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("%.3f", result.anomaly);
#endif
    ei_printf("]\n");
    int myBestClassificationNumber = -1;  
    float myBestClassificationValue = 0.25;   // lowest best allowable value
    
    // human-readable predictions
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);

       if (result.classification[ix].value > myBestClassificationValue ){
           myBestClassificationNumber = ix;                      // find the biggest array value
           myBestClassificationValue = result.classification[ix].value;  
        }
        int myCursorDown = 10*ix+20;
        display.setCursor(5, myCursorDown);  // move down the OLED
        int myTempResult = result.classification[ix].value * 100;
        if (ix > 0){
           display.println("#"+String(ix) + ": "+String(myTempResult)+"%,  " + String(myClassCount[ix])); 
        } else {

           display.println("#"+String(ix) + ": "+String(myTempResult)+"%, unknown"); 
        }
        
       // display.println( myTempResult ); 

        
    }

    
    digitalWrite(LEDB, HIGH);   //on board LED's are turned off by HIGH    
    digitalWrite(LEDG, HIGH);   
    digitalWrite(LEDR, HIGH); 








    // note: just ignore unknow readings
    // Should stop first later work on going slower
    //if (result.classification[0].value >= 0.4){ 
    if (myBestClassificationNumber == 0){    // 0 unknown label
      digitalWrite(LEDG, LOW);   
      digitalWrite(LEDR, LOW);   // kind of yellow
      
      display.setCursor(5,110);
      display.println("Unknown: " + String(myBestClassificationValue,2));
    } 
    
        
   // if (result.classification[1].value >= 0.6){  //BLUE on first object // can tune a bit here
  
    if (myBestClassificationNumber == 1){    // 1 Pop: Go Right
      digitalWrite(LEDB, LOW);
      myClassCount[1] += 1;
      
      display.setCursor(5,110);
      display.println("Pop: Go Right: " + String(myBestClassificationValue,2));
      // Should trun amount be related to classification strength?
      // first just a fixed turn

    } 
    
   // if (result.classification[2].value>= 0.1){  // green on second object    
    if (myBestClassificationNumber == 2){    // 2 water : go left
      digitalWrite(LEDG, LOW);   

      myClassCount[2] += 1;
      display.setCursor(5,110);
      display.println("Water: Go Left: " + String(myBestClassificationValue,2));
      
      // Should trun amount be related to classification strength?
      // first just a fixed turn
    } 
    
   // if (result.classification[3].value>= 0.1){   // red on third object
   
    if (myBestClassificationNumber == 3){    // 0 unknown label
      digitalWrite(LEDR, LOW);   // this not used in this model
      
      myClassCount[3] += 1; 
      display.setCursor(5,110);
      display.println("Go Faster: " + String(myBestClassificationValue,2));

      // first a fixed slowish (Max?) speed
      // later make it go faster to reach the max speed
    }
    
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif


  while (SerialLoRa.available()) {      // If anything comes in Serial (USB),
    Serial.print( SerialLoRa.read(),HEX);   // read it and send it out Serial1 (pins 0 & 1)
  }





/*   unbracket to grab an image of what the board sees   */

/*
    for (size_t ix = 0; ix < features_signal.total_length; ix++) {
        float value[1];
        features_signal.get_data(ix, 1, value);

        ei_printf("0x%06x", (int)value[0]);
        if (ix != features_signal.total_length - 1) {
          ei_printf(", ");
        }
    }



*/


     //display.setCursor(5,100);
     //display.println("Found: "+ String(myClassCount));
     display.display();  // OLED 4 bit 16 color GRAYSCALE update
        
  //delay(100);  

}

/**
 * @brief      Printf function uses vsnprintf and output using Arduino Serial
 *
 * @param[in]  format     Variable argument list
 */
void ei_printf(const char *format, ...) {

 #ifdef CORE_CM7  //The M4 core does not print
    static char print_buf[1024] = { 0 };

    va_list args;
    va_start(args, format);
    int r = vsnprintf(print_buf, sizeof(print_buf), format, args);
    va_end(args);

    if (r > 0) {
        Serial.write(print_buf);
    }
  #endif  
    
}
