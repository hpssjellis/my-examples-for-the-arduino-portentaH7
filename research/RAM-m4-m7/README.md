fast m4 to m7 to communicate between the cores using a shared RAM spacae

When I simplify the code it never works


Ideas from 

https://github.com/khoih-prog/Portenta_H7_Private/blob/main/KH_M4_core/M7_M4_sharemem_SRAM/M7_M4_sharemem_SRAM.ino


Change the length of any of  of these Serial Prints wrecks the program
See code here

[ram-4m-m7-05-works.in](https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/blob/master/research/RAM-m4-m7/ram-4m-m7-05-works.ino#L52-L63)




```
    Serial.println("================= Start Loop =================");
 
    
    localm7m4++;
    xfr_ptr -> M7toM4 = localm7m4;
    
    Serial.print("M7 to M4: "); Serial.println(xfr_ptr -> M7toM4);
    Serial.print("M4 to M7: "); Serial.println(xfr_ptr -> M4toM7);
    
    Serial.println("================= End Loop =================");
 
    Serial.println();
```



