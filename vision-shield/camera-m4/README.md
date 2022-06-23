




June 2022

[camera-v7-submitted.cpp](camera-v7-submitted.cpp) is a PR I will push to the [Arduino MBED core](https://github.com/arduino/ArduinoCore-mbed)


## GOT IT WORKING!

[camera-v6-better.cpp](camera-v6-better.cpp)  Replace the camera.cpp code with this file, then the camera works on both the M7 and the M4 core. 

## Following are the issues I had



Trying to get the camera working on the Portenta M4  core as per this issue on the arduino mbed core

https://github.com/arduino/ArduinoCore-mbed/issues/504





Very strange this line did not work

```#if defined(PORTENTA_H7_M7) || defined(PORTENTA_H7_M4)```

however this line was fine

```
#if  defined (CORE_CM7)  ||  defined (CORE_CM4)

```

Code presently dies here when grabbing the framebuffer
```int Camera::grabFrame(FrameBuffer &fb, uint32_t timeout)```

```



    HAL_DCMI_Suspend(&hdcmi);

    // Invalidate buffer after DMA transfer.
    SCB_InvalidateDCache_by_Addr((uint32_t*) framebuffer, framesize);

    return 0;
}


```




That function is in this location

```\cores\arduino\mbed\cmsis\CMSIS_5\CMSIS\TARGET_CORTEX_M\Include\cachel1_armv7.h  ```

and looks like this

```

/**
  \brief   D-Cache Invalidate by address
  \details Invalidates D-Cache for the given address.
           D-Cache is invalidated starting from a 32 byte aligned address in 32 byte granularity.
           D-Cache memory blocks which are part of given address + given size are invalidated.
  \param[in]   addr    address
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_FORCEINLINE void SCB_InvalidateDCache_by_Addr (volatile void *addr, int32_t dsize)
{
  #if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    if ( dsize > 0 ) {
       int32_t op_size = dsize + (((uint32_t)addr) & (__SCB_DCACHE_LINE_SIZE - 1U));
      uint32_t op_addr = (uint32_t)addr /* & ~(__SCB_DCACHE_LINE_SIZE - 1U) */;

      __DSB();

      do {
        SCB->DCIMVAC = op_addr;             /* register accepts only 32byte aligned values, only bits 31..5 are valid */
        op_addr += __SCB_DCACHE_LINE_SIZE;
        op_size -= __SCB_DCACHE_LINE_SIZE;
      } while ( op_size > 0 );

      __DSB();
      __ISB();
    }
  #endif
}


```

but I can't seem to link to it for it to run properly. Here is my present error message

```

C:\Arduino-1.8.19\portable\packages\arduino\hardware\mbed_portenta\3.1.1\libraries\Camera\src\camera.cpp: In member function 'int Camera::grabFrame(FrameBuffer&, uint32_t)':

C:\Arduino-1.8.19\portable\packages\arduino\hardware\mbed_portenta\3.1.1\libraries\Camera\src\camera.cpp:609:5: error: 'SCB_InvalidateDCache_by_Addr' was not declared in this scope

     SCB_InvalidateDCache_by_Addr((uint32_t*) framebuffer, framesize);

     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~


```






