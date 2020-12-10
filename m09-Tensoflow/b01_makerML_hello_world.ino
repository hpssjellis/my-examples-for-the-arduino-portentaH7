/*
 * b01_makerML_hello_world.ino
 * simplifying TensorflowLite Micro Machine Learning for all makers
 * 
 * 
 * 
 * By Jeremy Ellis 
 * Twitter @rocksetta
 * Website https://rocksetta.com
 * created Aug 20th, 2020 
 * Github    https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/tree/master/m09-Tensoflow
 *  
 *  
 *  Hashtags
 *  #TensorflowLiteMicro
 *  #TensorflowLiteForArduino
 *  #TinyMY
 *  #MakerML
 */



// By putting this model.h file here we can load everything as one file into the arduino IDER.
// Once it is working it is best to seperate this as a model.h file into it's own tabThis allows only one file for Arduino IDE, but you should seperate the following
// #include "model.h"  // uncomment when below has been put into it's own tab

/////////////////////////////////// cut and paste to model.h tab /////////////////////////////////////////////////////////////////



#pragma once

const unsigned char model_tflite[] = {
        0x18, 0x00, 0x00, 0x00, 0x54, 0x46, 0x4c, 0x33, 0x00, 0x00, 0x0e, 0x00,
        0x18, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x14, 0x00,
        0x0e, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x10, 0x0a, 0x00, 0x00,
        0xb8, 0x05, 0x00, 0x00, 0xa0, 0x05, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x0b, 0x00, 0x00, 0x00, 0x90, 0x05, 0x00, 0x00, 0x7c, 0x05, 0x00, 0x00,
        0x24, 0x05, 0x00, 0x00, 0xd4, 0x04, 0x00, 0x00, 0xc4, 0x00, 0x00, 0x00,
        0x74, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
        0x14, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x54, 0xf6, 0xff, 0xff, 0x58, 0xf6, 0xff, 0xff, 0x5c, 0xf6, 0xff, 0xff,
        0x60, 0xf6, 0xff, 0xff, 0xc2, 0xfa, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
        0x40, 0x00, 0x00, 0x00, 0xd0, 0x37, 0xed, 0xbd, 0xb6, 0x38, 0xf9, 0x3e,
        0xc6, 0x9d, 0x00, 0x3f, 0x1a, 0xb0, 0x05, 0xbe, 0xc6, 0x49, 0xd9, 0xbe,
        0x55, 0x62, 0x8b, 0xbe, 0xfa, 0xa9, 0x86, 0x3e, 0xc4, 0x4d, 0x9c, 0x3e,
        0x85, 0x7c, 0x8d, 0xbe, 0x44, 0xf3, 0x2c, 0xbe, 0xb5, 0x07, 0x56, 0x3e,
        0xb3, 0x84, 0x49, 0x3e, 0x60, 0x35, 0xa8, 0xbc, 0x60, 0xbc, 0xcf, 0xbe,
        0x23, 0x52, 0xff, 0x3e, 0xc6, 0xaf, 0x39, 0xbe, 0x0e, 0xfb, 0xff, 0xff,
        0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x36, 0xec, 0xe2, 0x3d, 0x87, 0xea, 0x53, 0xbf, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0xef, 0xfb, 0x3e,
        0x5a, 0x6f, 0x2b, 0xbe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x1b, 0x1f, 0x12, 0xbf, 0xb4, 0xef, 0xec, 0xbd, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x2e, 0x32, 0x8f, 0xbf, 0x00, 0x00, 0x00, 0x00,
        0x5a, 0xfb, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
        0xdd, 0xec, 0x8d, 0xbe, 0x42, 0xef, 0x55, 0x3d, 0xdd, 0xdd, 0x18, 0x3e,
        0x6b, 0x54, 0xaa, 0x3e, 0xa5, 0xa5, 0xa6, 0x3e, 0xf4, 0x12, 0xe7, 0xbd,
        0x06, 0x6a, 0x4b, 0xbe, 0xf7, 0x32, 0x14, 0x3e, 0xa4, 0xe2, 0xb0, 0xbe,
        0x0c, 0x83, 0xe1, 0x3d, 0x88, 0xf6, 0xf1, 0x3e, 0x6b, 0x71, 0x0e, 0x3c,
        0xde, 0xed, 0x77, 0x3e, 0x92, 0x91, 0x23, 0x3e, 0x08, 0xb4, 0x1b, 0xbe,
        0x9d, 0x9b, 0xa8, 0xbe, 0x77, 0x35, 0x9e, 0xbe, 0x42, 0x29, 0x20, 0xbf,
        0x07, 0x20, 0x45, 0x3e, 0x3e, 0x92, 0xc3, 0xbe, 0x36, 0xca, 0x10, 0xbe,
        0xef, 0x96, 0xc0, 0xbe, 0x8c, 0xa8, 0xcf, 0x3d, 0xe5, 0xbe, 0xfc, 0x3d,
        0x44, 0x5a, 0xf8, 0x3d, 0x92, 0x68, 0xd4, 0xbe, 0x3d, 0x18, 0x8f, 0x3e,
        0xae, 0x9a, 0x45, 0x3d, 0x1b, 0x8b, 0xb8, 0xbe, 0x40, 0x3d, 0x8c, 0xbd,
        0x2f, 0x90, 0x2d, 0xbf, 0x8a, 0x81, 0x1a, 0x3e, 0x04, 0x8f, 0x5c, 0xbe,
        0x4c, 0xb8, 0xe1, 0xbd, 0x62, 0x66, 0x59, 0xbe, 0xe6, 0xb4, 0xb4, 0xbe,
        0xe6, 0x74, 0x3f, 0x3e, 0xfc, 0x40, 0xaf, 0x3d, 0x25, 0x72, 0x50, 0x3e,
        0x47, 0xec, 0xcc, 0x3e, 0x86, 0x9e, 0x70, 0x3e, 0x2a, 0x3b, 0x67, 0x3e,
        0xad, 0xf5, 0xcf, 0xbc, 0x30, 0x4d, 0x0d, 0x3e, 0xfc, 0xb9, 0xd0, 0x3d,
        0xcf, 0xa8, 0xc0, 0xbe, 0x7c, 0x8e, 0xe8, 0x3e, 0x18, 0x76, 0x14, 0xbe,
        0x76, 0x3f, 0x84, 0xbe, 0x4c, 0xd6, 0x46, 0x3d, 0x49, 0x07, 0xca, 0x3e,
        0x90, 0x87, 0xa0, 0xbd, 0xa5, 0x7d, 0xdd, 0xbe, 0xe5, 0x4a, 0xa5, 0x3e,
        0x0d, 0x6e, 0xff, 0xbd, 0xbc, 0x53, 0xb3, 0xbe, 0x57, 0x58, 0x92, 0x3e,
        0x29, 0x9e, 0x91, 0x3e, 0x24, 0x25, 0xd5, 0x3e, 0xe5, 0x06, 0x07, 0xbe,
        0x2a, 0xd4, 0xb8, 0xbe, 0xcc, 0xe4, 0x02, 0xbe, 0x68, 0x7b, 0x95, 0x3e,
        0xc1, 0x45, 0xcc, 0xbe, 0x4b, 0xb3, 0x82, 0x3e, 0x25, 0xae, 0x00, 0xbf,
        0x29, 0xdc, 0xb4, 0xbe, 0xfe, 0x09, 0x60, 0x3e, 0x0f, 0x43, 0xc7, 0x3e,
        0xc4, 0xf8, 0xcd, 0xbd, 0x1d, 0x74, 0xc1, 0xbe, 0xf4, 0xc8, 0x5c, 0x3e,
        0xe6, 0xaf, 0x0b, 0x3e, 0x98, 0x01, 0xa6, 0xbd, 0x96, 0xb4, 0x90, 0xbe,
        0x78, 0x41, 0xc3, 0xbe, 0xfd, 0x30, 0xc1, 0x3e, 0x15, 0x7f, 0xcb, 0x3e,
        0xb3, 0x97, 0x0a, 0x3e, 0x97, 0x4d, 0xa9, 0x3e, 0x2f, 0x97, 0xa5, 0x3e,
        0x24, 0x1c, 0xea, 0x3d, 0x6a, 0x7e, 0x39, 0x3e, 0x83, 0x3b, 0x61, 0xbe,
        0xd8, 0x55, 0x6d, 0x3d, 0xe1, 0x22, 0xd9, 0x3e, 0xc0, 0x09, 0x88, 0xbe,
        0x42, 0x55, 0xdb, 0xbe, 0xfa, 0x71, 0x73, 0x3e, 0x0d, 0x35, 0x88, 0xbe,
        0xf1, 0x67, 0xc9, 0x3e, 0xa0, 0x1f, 0x76, 0xbc, 0x81, 0xe0, 0xa0, 0x3e,
        0xc0, 0x11, 0x1c, 0x3d, 0x04, 0x30, 0x6a, 0xbe, 0x2a, 0x9c, 0x4c, 0x3e,
        0x1f, 0x99, 0xad, 0x3e, 0x3f, 0xe9, 0x5a, 0x3d, 0xee, 0xaa, 0xce, 0x3e,
        0xd1, 0x44, 0xc6, 0x3e, 0x9b, 0xaa, 0x57, 0xbe, 0x43, 0x1f, 0x8f, 0xbe,
        0x34, 0x8a, 0x9a, 0xbd, 0xbd, 0x92, 0x6e, 0x3e, 0xc1, 0xc1, 0x3c, 0xbe,
        0x1f, 0x30, 0x43, 0xbe, 0x45, 0xe6, 0xb5, 0xbc, 0xce, 0xa5, 0x93, 0xbe,
        0x56, 0xea, 0x1a, 0xbe, 0x47, 0x05, 0xab, 0x3e, 0xc0, 0xd0, 0xcd, 0x3e,
        0x25, 0x60, 0x8d, 0x3e, 0xb6, 0xf2, 0x50, 0x3e, 0x93, 0x4c, 0x09, 0x3d,
        0xca, 0x36, 0x9d, 0x3e, 0xcf, 0xd3, 0xa0, 0xbe, 0xfa, 0x86, 0x00, 0x3e,
        0xe0, 0xfb, 0x8c, 0xbd, 0xb2, 0x8a, 0xbf, 0x3e, 0xc3, 0x70, 0xa9, 0xbe,
        0x21, 0x43, 0x84, 0x3e, 0x5a, 0x16, 0x16, 0x3e, 0xc4, 0x0b, 0x28, 0x3d,
        0xb9, 0x09, 0x51, 0xbe, 0xda, 0xcc, 0x04, 0xbe, 0xd9, 0x4b, 0x8a, 0x3e,
        0x8f, 0x22, 0x93, 0x3d, 0x72, 0xfe, 0x2d, 0xbe, 0x8e, 0x0d, 0x13, 0xbe,
        0xa1, 0x47, 0xe4, 0xbe, 0x03, 0x52, 0xe0, 0x3e, 0xd2, 0xdc, 0x5c, 0xbe,
        0x63, 0xab, 0x83, 0x3e, 0x14, 0x07, 0x92, 0x3d, 0xe8, 0xa4, 0x7e, 0x3d,
        0x16, 0xc6, 0x92, 0x3e, 0xd4, 0x76, 0x95, 0xbe, 0xf0, 0xdc, 0xc4, 0xbd,
        0xec, 0x5e, 0x74, 0x3e, 0x0c, 0x08, 0xc7, 0x3e, 0x66, 0xc0, 0x9c, 0xbe,
        0x6c, 0xf6, 0xdd, 0xbd, 0x77, 0x7e, 0x74, 0x3e, 0xc0, 0xfb, 0xdd, 0x3b,
        0x7e, 0x00, 0x08, 0xbe, 0xa0, 0x2e, 0x9f, 0xbc, 0xe0, 0xc5, 0xbf, 0x3c,
        0x22, 0xcc, 0x95, 0xbe, 0x00, 0x90, 0x80, 0x3a, 0x48, 0x39, 0x5c, 0xbd,
        0x02, 0x1c, 0x06, 0xbe, 0x60, 0x32, 0xdd, 0xbc, 0x9c, 0xfb, 0x99, 0xbe,
        0xb0, 0xc2, 0x0d, 0xbd, 0x28, 0x33, 0x42, 0xbd, 0x90, 0x1f, 0x82, 0xbd,
        0x09, 0xd4, 0xd9, 0x3e, 0xa4, 0x79, 0xf0, 0x3d, 0xe6, 0x5b, 0x21, 0xbe,
        0x6d, 0xa2, 0xbe, 0xbe, 0xae, 0x26, 0xc9, 0xbe, 0x76, 0x50, 0xeb, 0x3d,
        0x5e, 0x01, 0x86, 0x3e, 0x67, 0xbd, 0xdc, 0x3e, 0x78, 0x38, 0x8a, 0xbe,
        0x74, 0xc3, 0xec, 0x3d, 0x70, 0xc9, 0xd0, 0x3e, 0xc3, 0xfe, 0x5a, 0xbd,
        0xd8, 0x69, 0x31, 0xbd, 0x3b, 0xdb, 0x7f, 0xbe, 0x12, 0x35, 0x58, 0xbe,
        0xb0, 0x3a, 0x81, 0x3e, 0xcc, 0xa0, 0x17, 0xbe, 0x32, 0xad, 0x48, 0x3e,
        0x1f, 0x35, 0x8d, 0x3e, 0xec, 0xfe, 0xd4, 0x3d, 0xef, 0x33, 0x7b, 0xbe,
        0xce, 0x81, 0x9e, 0xbe, 0x02, 0x7a, 0x5a, 0x3e, 0xa7, 0xb6, 0xd5, 0xbe,
        0xae, 0x04, 0x0c, 0x3e, 0x95, 0x40, 0xd1, 0x3e, 0x87, 0xfe, 0x1b, 0x3e,
        0x61, 0xf3, 0x82, 0xbe, 0x00, 0xcd, 0x3c, 0xbd, 0x03, 0x7d, 0x8b, 0x3e,
        0x20, 0xfd, 0xcb, 0x3c, 0x80, 0x33, 0x99, 0xbc, 0x09, 0xad, 0x68, 0xbe,
        0x7a, 0xff, 0x75, 0x3e, 0x11, 0xba, 0x6d, 0xbe, 0x30, 0xe3, 0x31, 0x3d,
        0x00, 0xfa, 0xc1, 0xbd, 0x9f, 0x38, 0xa3, 0xbe, 0x97, 0x88, 0x28, 0xbe,
        0x37, 0x72, 0x3c, 0xbe, 0x58, 0xc6, 0x86, 0xbd, 0x62, 0xdf, 0x70, 0x3e,
        0xb5, 0xef, 0xb8, 0x3c, 0x16, 0x67, 0x87, 0x3e, 0xce, 0x77, 0xb4, 0xbe,
        0x20, 0x52, 0x64, 0x3d, 0xa8, 0xcc, 0xbc, 0xbd, 0x17, 0x62, 0x49, 0xbb,
        0x42, 0x13, 0x49, 0x3e, 0xa6, 0x0a, 0x14, 0x3e, 0x95, 0xc9, 0x37, 0xbe,
        0x8c, 0x10, 0xb2, 0xbe, 0xe1, 0x11, 0x6f, 0xbe, 0x46, 0x45, 0x73, 0x3e,
        0xf0, 0x26, 0xbc, 0xbe, 0xc0, 0x4f, 0x88, 0xbb, 0x39, 0x0a, 0xbb, 0x3e,
        0x0f, 0x32, 0x88, 0x3e, 0xf0, 0x81, 0x99, 0x3e, 0x3f, 0xd5, 0x8c, 0xbe,
        0x10, 0x59, 0x4f, 0xbd, 0x63, 0x85, 0xb6, 0x3e, 0x6a, 0xe4, 0x98, 0xbf,
        0x6b, 0x1a, 0xa8, 0xbe, 0xc8, 0x77, 0xb5, 0xbe, 0x80, 0xea, 0x3f, 0xbd,
        0x6d, 0x91, 0xac, 0xbe, 0xd2, 0xdd, 0x63, 0xbe, 0x41, 0xcb, 0x59, 0xbe,
        0xb6, 0x0f, 0x94, 0xbe, 0x45, 0x12, 0x89, 0x3e, 0x4f, 0x6f, 0xb8, 0x3e,
        0x08, 0xa5, 0x02, 0xbd, 0x12, 0x74, 0xa8, 0xbe, 0x56, 0x2f, 0xa6, 0xbe,
        0x9e, 0xd8, 0x11, 0xbd, 0x3e, 0xdd, 0x67, 0x3e, 0x3e, 0xa8, 0x1a, 0x3e,
        0x81, 0x8c, 0x9c, 0x3e, 0x9f, 0x5b, 0x96, 0x3d, 0x9c, 0x65, 0xca, 0x3d,
        0xb4, 0x3c, 0xd2, 0xbe, 0x91, 0x2a, 0x45, 0x3e, 0x63, 0x53, 0x9c, 0x3e,
        0x99, 0x85, 0x42, 0xbe, 0xfc, 0xaf, 0x04, 0xbe, 0x12, 0xd7, 0x88, 0xbe,
        0xfa, 0xc2, 0xc5, 0xbe, 0x71, 0x2f, 0x96, 0x3e, 0xe5, 0x0b, 0x93, 0x3e,
        0xb8, 0x85, 0xf4, 0x3d, 0x37, 0x48, 0xcd, 0xbe, 0xa1, 0xc8, 0x63, 0xbe,
        0x5a, 0xa0, 0x3c, 0x3e, 0x4d, 0x84, 0x1e, 0x3b, 0x79, 0x40, 0x50, 0x3e,
        0xcb, 0xb1, 0xd0, 0x3e, 0xe1, 0x10, 0xcd, 0x3e, 0x7f, 0x3c, 0xcd, 0x3e,
        0xb8, 0xda, 0x37, 0xbe, 0x66, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
        0x40, 0x00, 0x00, 0x00, 0x9c, 0x4f, 0xd6, 0xbe, 0x7d, 0xdb, 0xf3, 0x3e,
        0x6b, 0x2b, 0xaa, 0xbe, 0xc1, 0x26, 0x26, 0xbf, 0xee, 0x03, 0x1f, 0x3f,
        0x00, 0x00, 0x00, 0x00, 0x37, 0xab, 0xa7, 0xbe, 0xd0, 0x10, 0x5b, 0x3e,
        0xe5, 0xbc, 0xca, 0xbe, 0x00, 0x00, 0x00, 0x00, 0x94, 0x4a, 0x48, 0x3e,
        0xc3, 0x7d, 0x2f, 0xbd, 0x27, 0xef, 0x9b, 0xbd, 0x32, 0x58, 0x48, 0x3f,
        0xfc, 0x3b, 0xda, 0xbb, 0x18, 0xfd, 0x60, 0xbd, 0xb2, 0xff, 0xff, 0xff,
        0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xa8, 0xde, 0x92, 0x39,
        0x4a, 0x26, 0x8b, 0xbf, 0xb9, 0x79, 0x8c, 0x3e, 0xc1, 0xb8, 0x1e, 0x40,
        0xde, 0x0b, 0x9d, 0xbf, 0x0e, 0xe2, 0x61, 0xbe, 0xdc, 0x1b, 0xb1, 0x3e,
        0x47, 0x15, 0x60, 0xbe, 0x8c, 0x3c, 0x06, 0x3f, 0xfc, 0x69, 0xcf, 0x3e,
        0xd0, 0x07, 0x15, 0xbf, 0xa7, 0x92, 0x25, 0x3e, 0xf6, 0xf8, 0xbc, 0x3e,
        0x31, 0xe1, 0xd4, 0x3f, 0x3f, 0xf6, 0x02, 0x3f, 0x78, 0xf2, 0x02, 0x3d,
        0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xaf, 0x96, 0x93, 0xbe,
        0xb8, 0xfb, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x54, 0x4f, 0x43, 0x4f,
        0x20, 0x43, 0x6f, 0x6e, 0x76, 0x65, 0x72, 0x74, 0x65, 0x64, 0x2e, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00,
        0x04, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x00, 0x00,
        0xf0, 0x00, 0x00, 0x00, 0xe4, 0x00, 0x00, 0x00, 0xd8, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00,
        0x48, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xce, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x08, 0x18, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x1c, 0xfc, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
        0x14, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x10, 0x00,
        0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x00, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xba, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
        0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x16, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x10, 0x00, 0x0e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x08, 0x24, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
        0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x07, 0x00,
        0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x0a, 0x00, 0x00, 0x00, 0x10, 0x03, 0x00, 0x00, 0xa4, 0x02, 0x00, 0x00,
        0x40, 0x02, 0x00, 0x00, 0xf4, 0x01, 0x00, 0x00, 0xac, 0x01, 0x00, 0x00,
        0x48, 0x01, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0xb4, 0x00, 0x00, 0x00,
        0x50, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x26, 0xfd, 0xff, 0xff,
        0x3c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x18, 0xfd, 0xff, 0xff, 0x20, 0x00, 0x00, 0x00,
        0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31,
        0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x34, 0x2f, 0x4d, 0x61, 0x74,
        0x4d, 0x75, 0x6c, 0x5f, 0x62, 0x69, 0x61, 0x73, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x6e, 0xfd, 0xff, 0xff,
        0x50, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x60, 0xfd, 0xff, 0xff, 0x34, 0x00, 0x00, 0x00,
        0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31,
        0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x34, 0x2f, 0x4d, 0x61, 0x74,
        0x4d, 0x75, 0x6c, 0x2f, 0x52, 0x65, 0x61, 0x64, 0x56, 0x61, 0x72, 0x69,
        0x61, 0x62, 0x6c, 0x65, 0x4f, 0x70, 0x2f, 0x74, 0x72, 0x61, 0x6e, 0x73,
        0x70, 0x6f, 0x73, 0x65, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xce, 0xfd, 0xff, 0xff,
        0x34, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0xc0, 0xfd, 0xff, 0xff, 0x19, 0x00, 0x00, 0x00,
        0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31,
        0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x33, 0x2f, 0x52, 0x65, 0x6c,
        0x75, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00, 0x12, 0xfe, 0xff, 0xff, 0x3c, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x04, 0xfe, 0xff, 0xff, 0x20, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75,
        0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31, 0x2f, 0x64, 0x65, 0x6e,
        0x73, 0x65, 0x5f, 0x33, 0x2f, 0x4d, 0x61, 0x74, 0x4d, 0x75, 0x6c, 0x5f,
        0x62, 0x69, 0x61, 0x73, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00, 0x5a, 0xfe, 0xff, 0xff, 0x50, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x4c, 0xfe, 0xff, 0xff, 0x34, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75,
        0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31, 0x2f, 0x64, 0x65, 0x6e,
        0x73, 0x65, 0x5f, 0x33, 0x2f, 0x4d, 0x61, 0x74, 0x4d, 0x75, 0x6c, 0x2f,
        0x52, 0x65, 0x61, 0x64, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65,
        0x4f, 0x70, 0x2f, 0x74, 0x72, 0x61, 0x6e, 0x73, 0x70, 0x6f, 0x73, 0x65,
        0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00, 0xba, 0xfe, 0xff, 0xff, 0x34, 0x00, 0x00, 0x00,
        0x0a, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0xac, 0xfe, 0xff, 0xff, 0x19, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75,
        0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31, 0x2f, 0x64, 0x65, 0x6e,
        0x73, 0x65, 0x5f, 0x32, 0x2f, 0x52, 0x65, 0x6c, 0x75, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0xfe, 0xfe, 0xff, 0xff, 0x3c, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
        0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xf0, 0xfe, 0xff, 0xff,
        0x20, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69,
        0x61, 0x6c, 0x5f, 0x31, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32,
        0x2f, 0x4d, 0x61, 0x74, 0x4d, 0x75, 0x6c, 0x5f, 0x62, 0x69, 0x61, 0x73,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x46, 0xff, 0xff, 0xff, 0x50, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x38, 0xff, 0xff, 0xff,
        0x34, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69,
        0x61, 0x6c, 0x5f, 0x31, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32,
        0x2f, 0x4d, 0x61, 0x74, 0x4d, 0x75, 0x6c, 0x2f, 0x52, 0x65, 0x61, 0x64,
        0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x4f, 0x70, 0x2f, 0x74,
        0x72, 0x61, 0x6e, 0x73, 0x70, 0x6f, 0x73, 0x65, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0xa6, 0xff, 0xff, 0xff, 0x48, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
        0x2c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00,
        0x04, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x43,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
        0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32, 0x5f, 0x69, 0x6e, 0x70, 0x75,
        0x74, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x04, 0x00,
        0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x0e, 0x00, 0x00, 0x00,
        0x28, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x49, 0x64, 0x65, 0x6e, 0x74, 0x69, 0x74, 0x79,
        0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x0a, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00,
        0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03, 0x00, 0x00, 0x00
}; 
unsigned int model_tflite_len = 2640;


//////////////////////////////////// end cut and paste to model.h tab ///////////////////////////////////////////////////////////////


#include "Arduino.h"
#include <TensorFlowLite.h>


/*================= Start Advanced Area ===============================*/

#include "tensorflow/lite/micro/all_ops_resolver.h"
//#include "tensorflow/lite/micro/kernels/micro_ops.h"
//#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"

#include "tensorflow/lite/micro/micro_error_reporter.h"  // may have issues on M4 core
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "tensorflow/lite/c/common.h"
//#include "tensorflow/lite/c/c_api.h" // has interesting funcitons, not in main library


// Start Debug.cc information    ----------------------------------------------------------


 //  Note: CORE_CM7 deprecated as of MBED 1.3.0 , new names are:  PORTENTA_H7_M7,  ARDUINO_NANO33BLE
 #if  defined (CORE_CM7)   ||  defined (PORTENTA_H7_M7) ||  defined (ARDUINO_NANO33BLE) ||  defined (YOUR_BOARD1) // CORE_CM7 is for the PortentaH7 outer core
 
    // do abosolutely nothing the default works

 // Note: CORE_CM4, NANO_33_BLE deprecated as MBED of 1.30, new names: PORTENTA_H7_M4 see above for Nano33BLE   
 #elif defined (CORE_CM4) ||  defined (PORTENTA_H7_M4) || defined (NANO_33_BLE)   ||  defined (YOUR_BOARD2)  // CORE_CM4 is for the PortentaH7 inner core
 
     #define DEBUG_SERIAL_OBJECT (Serial) 

     extern "C" void DebugLog(const char* s) {
        static bool is_initialized = false;
        if (!is_initialized) {
           DEBUG_SERIAL_OBJECT.begin(9600);
           is_initialized = true;
        }
        DEBUG_SERIAL_OBJECT.print(s);
     }

 #elif defined (__SAM3X8E__)  ||  defined (YOUR_BOARD3) // Arduino UNO style boards

     #define DEBUG_SERIAL_OBJECT (SerialUSB) 

     extern "C" void DebugLog(const char* s) {
        static bool is_initialized = false;
        if (!is_initialized) {
           DEBUG_SERIAL_OBJECT.begin(9600);
           is_initialized = true;
        }
        DEBUG_SERIAL_OBJECT.print(s);
     }
 #elif defined (SEEED_XIAO_M0)  ||  defined (YOUR_BOARD4) // The new $5 USD Seeeduino XIAO board

     #define CFG_TUSB_DEBUG
     
 #else
   // don't do any debugging until you figure out your board  
   
   extern "C" void DebugLog(const char* s) {
     // Do not log debug info
   } 
 #endif


/*
 * nano_33_iot.build.board=SAMD_NANO_33_IOT  // have not got it working yet
 * 
*/

// End Debug.cc information    ----------------------------------------------------------


namespace { // Start namespace----------------------------------------------------------

   // define needed variables
   tflite::ErrorReporter* error_reporter = nullptr;
   const tflite::Model* model = nullptr;
   tflite::MicroInterpreter* interpreter = nullptr;
   TfLiteTensor* input = nullptr;
   TfLiteTensor* output = nullptr;
   // Create an area of memory to use for input, output, and intermediate arrays.
   constexpr int kTensorArenaSize = 2 * 1024;  // I like 20 * 1024;
   uint8_t tensor_arena[kTensorArenaSize];

}  // END namespace----------------------------------------------------------



/*================= End Advanced Area ===============================*/


/*================= Start Smart Area ================================*/


void modelSetup(const unsigned char theModel[]){

  // NOLINTNEXTLINE(runtime-global-variables)
  
   static tflite::MicroErrorReporter micro_error_reporter;
  
   error_reporter = &micro_error_reporter;  

   // Map the model into a usable data structure. This doesn't involve any
   // copying or parsing, it's a very lightweight operation.


   model = tflite::GetModel(theModel);  // name from the tflite converter model.h file

  
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)

  
  static tflite::AllOpsResolver resolver;


  /* // replace the above line if you know each operation to save space
  
  static tflite::MicroMutableOpResolver<5> micro_op_resolver;  // NOLINT
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_DEPTHWISE_CONV_2D,tflite::ops::micro::Register_DEPTHWISE_CONV_2D() );
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_MAX_POOL_2D,tflite::ops::micro::Register_MAX_POOL_2D() );
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_CONV_2D,tflite::ops::micro::Register_CONV_2D() );
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_FULLY_CONNECTED,tflite::ops::micro::Register_FULLY_CONNECTED() );
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_SOFTMAX,tflite::ops::micro::Register_SOFTMAX() );

   * 
   */
   

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);
 
}


float modelPredict(float myInput){   // like tensorflowJS  const myPredictArray = await model.predict(xTrainingData).data()  
  
  input->data.f[0] = myInput;  // may have to edit this

  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
  
  // if (invoke_status != kTfLiteOk) {
  //    Serial.print("Error with input: " + String(myInput));
  // }

  return output->data.f[0];   // may have to edit this
}


/*================= End Smart Area ======================================*/


/*================= Start Maker Area ======================================*/


int myCounter = 0;
int myLed = LED_BUILTIN;   //or 7 or 5 or LED_BUILTIN or LEDB

void setup() {
  
  Serial.begin(9600);
  pinMode(myLed, OUTPUT);
  modelSetup(model_tflite);  // name of the model in the tab model.h
  
}


void loop() {
   myCounter +=1;
    if (myCounter >= 360){
        myCounter = 0;
    }
    
    float x_val = myCounter * 3.14/180;  // degrees to radians
    float y_val = sin(x_val);

    // This uses your model to make a prediction
    float predicted = modelPredict(x_val);

    Serial.println("sin(" +String(x_val)+ ") = " + String(y_val) + "\t predicted: " + String(predicted) );


    // y=1 LED is fully on. The LED's brightness can range from 0-255.
    int brightness = (int)(127.5f * (predicted+1));

     #if  defined (CORE_CM7)  ||  defined (CORE_CM4)

         if (brightness <= 128){
              digitalWrite(myLed, HIGH);  // means off
         } else {
               digitalWrite(myLed, LOW);  // means on             
         }
     #else
         analogWrite(myLed, brightness);  // not on Porttenta
     #endif 



    delay(3); // slows the process down a bit to see the sine wave

  
}


/*================= End Maker Area ======================================*/
