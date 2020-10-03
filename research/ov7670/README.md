Trying to get the ov7670 camera to work


good links





Here is the processing program that helps you view the data from the camera https://processing.org/download/support.html

use the processing.txt sketch and change line 37 ish about your port used. takes about 6 seconds to load.








Here is a good blog: 
https://blog.arduino.cc/2020/06/24/machine-vision-with-low-cost-camera-modules/








# other referencces

https://circuitdigest.com/microcontroller-projects/how-to-use-ov7670-camera-module-with-arduino


video https://www.youtube.com/watch?v=S2yTQHM82jc


[original esp32 demo](https://www.youtube.com/redirect?event=video_description&v=S2yTQHM82jc&redir_token=QUFFLUhqa3pYY1NKWjZSSzlSM19Vc0RiVUVfdDJaNEh4QXxBQ3Jtc0trRFViQlV3cXY4SVZ1TG9NVWxQNjF5bmJFVlc1cU5HVEtwYmU4MlBMQWFZc1RMZkVqQnJ6aG1XbWNOdDkzdmticmVKb1dFeks2MHlCQ3FINE9NSlJBaXRlejdCNXpmS2h0Q3hmQkxDQndYSkZaUjRZTQ%3D%3D&q=https%3A%2F%2Fgithub.com%2Figrr%2Fesp32-cam-demo)


Great blog about apples and oranges  
Conversions to RGB565  https://eloquentarduino.github.io/2020/01/image-recognition-with-esp32-and-arduino/


downsize
```
uint16_t rgb_frame[HEIGHT / BLOCK_SIZE][WIDTH / BLOCK_SIZE][3] = { 0 };

void grab_image() {
    for (size_t i = 0; i < len; i += 2) {
        // get r, g, b from the buffer
        // see later

        const size_t j = i / 2;
        // transform x, y in the original image to x, y in the downsampled image
        // by dividing by BLOCK_SIZE
        const uint16_t x = j % WIDTH;
        const uint16_t y = floor(j / WIDTH);
        const uint8_t block_x = floor(x / BLOCK_SIZE);
        const uint8_t block_y = floor(y / BLOCK_SIZE);

        // average pixels in block (accumulate)
        rgb_frame[block_y][block_x][0] += r;
        rgb_frame[block_y][block_x][1] += g;
        rgb_frame[block_y][block_x][2] += b;
    }
}

```
    





extract rgb565
```
config.pixel_format = PIXFORMAT_RGB565;

for (size_t i = 0; i < len; i += 2) {
    const uint8_t high = buf[i];
    const uint8_t low  = buf[i+1];
    const uint16_t pixel = (high << 8) | low;

    const uint8_t r = (pixel & 0b1111100000000000) >> 11;
    const uint8_t g = (pixel & 0b0000011111100000) >> 6;
    const uint8_t b = (pixel & 0b0000000000011111);
}
```



grab image 
```
#define H (HEIGHT / BLOCK_SIZE)
#define W (WIDTH / BLOCK_SIZE)

void linearize_features() {
  size_t i = 0;
  double features[H*W*3] = {0};

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      features[i++] = rgb_frame[y][x][0];
      features[i++] = rgb_frame[y][x][1];
      features[i++] = rgb_frame[y][x][2];
    }
  }

  // print to serial
  for (size_t i = 0; i < H*W*3; i++) {
    Serial.print(features[i]);
    Serial.print('\t');
  }

  Serial.println();
}

```



