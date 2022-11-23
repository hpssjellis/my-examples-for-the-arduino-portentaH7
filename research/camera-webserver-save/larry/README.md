Looks like [a03.ino](a03.ino) is working. Thanks for the help. Next issue is the camera framebuffer.




My best ideas so far. 

[a01](ao1.ino)  is trying to edit your code, but always has some compiler issues. This can be tested without the Portenta as the issue is compiling it.

Compile issue at [here](https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/blob/42e591f29604f498ca8ee786af78ac8596856654/research/camera-webserver-save/larry/a01.ino#L113)

```
  rc = png.open("fs/testimg.png", myOpen, myClose, myRead, myWrite, mySeek);

```


[a02](a02.ino) is what I am having most success with as I build from what works.

Latest issue is finding the storage spot for the combined PNG

This line is not working to dump the entire PNG to disk [here](https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/blob/42e591f29604f498ca8ee786af78ac8596856654/research/camera-webserver-save/larry/a02.ino#L71)

```
            fprintf(myPngFile, (const char *)ucOut, sizeof(ucOut) );    
```


Notes:

This is how the bmp file saving was done [here](https://github.com/arduino-libraries/Arduino_Pro_Tutorials/blob/main/examples/Vision%20Shield%20to%20SD%20Card%20bmp/visionShieldBitmap/visionShieldBitmap.ino)

 ```
 // Settings for our setup
#define IMAGE_HEIGHT (unsigned int)240
#define IMAGE_WIDTH (unsigned int)320
#define IMAGE_MODE CAMERA_GRAYSCALE
#define BITS_PER_PIXEL (unsigned int)8
#define PALETTE_COLORS_AMOUNT (unsigned int)(pow(2, BITS_PER_PIXEL))
#define PALETTE_SIZE  (unsigned int)(PALETTE_COLORS_AMOUNT * 4) // 4 bytes = 32bit per color (3 bytes RGB and 1 byte 0x00)
#define IMAGE_PATH "/fs/image.bmp"

// Headers info
#define BITMAP_FILE_HEADER_SIZE (unsigned int)14 // For storing general information about the bitmap image file
#define DIB_HEADER_SIZE (unsigned int)40 // For storing information about the image and define the pixel format
#define HEADER_SIZE (BITMAP_FILE_HEADER_SIZE + DIB_HEADER_SIZE)
 
 ...
     // Bitmap structure (Head + DIB Head + ColorMap + binary image)
    unsigned char bitmapFileHeader[BITMAP_FILE_HEADER_SIZE];
    unsigned char bitmapDIBHeader[DIB_HEADER_SIZE];
    unsigned char colorMap[PALETTE_SIZE]; // Needed for <= 8bpp grayscale bitmaps   
 
    fwrite(bitmapFileHeader, 1, BITMAP_FILE_HEADER_SIZE, file);
    fwrite(bitmapDIBHeader, 1, DIB_HEADER_SIZE, file);
    fwrite(colorMap, 1, PALETTE_SIZE, file);
    fwrite(imageData, 1, IMAGE_HEIGHT * IMAGE_WIDTH, file);

 
 ```
