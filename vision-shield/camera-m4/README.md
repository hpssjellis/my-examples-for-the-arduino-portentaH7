




June 2022





Trying to get the camera working on the Portenta M4  core as per this issue on the arduino mbed core

https://github.com/arduino/ArduinoCore-mbed/issues/504


Code presently dies here when grabbing the framebuffer
```int Camera::grabFrame(FrameBuffer &fb, uint32_t timeout)```

```



    HAL_DCMI_Suspend(&hdcmi);

    // Invalidate buffer after DMA transfer.
    SCB_InvalidateDCache_by_Addr((uint32_t*) framebuffer, framesize);

    return 0;
}


```




That function is in this locaiton

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

not sure why the file isnot linked to.






