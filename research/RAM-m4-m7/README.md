fast m4 to m7 to communicate between the cores using a shared RAM spacae

When I simplify the code it never works


Ideas from 

https://github.com/khoih-prog/Portenta_H7_Private/blob/main/KH_M4_core/M7_M4_sharemem_SRAM/M7_M4_sharemem_SRAM.ino


Change the length of any of  of these Serial Prints wrecks the program
See code here

[ram-4m-m7-05-works.in](https://github.com/khoih-prog/Portenta_H7_Private/blob/main/KH_M4_core/M7_M4_sharemem_SRAM/M7_M4_sharemem_SRAM.ino#L57-L66)




```
    Serial.println("================= Start Loop =================");
   // digitalWrite(LEDR, LOW);
    xfr_ptr -> M7toM4 = localm7m4;
    localm7m4++;
    Serial.print("Writing M7 to M4, value = "); Serial.println(xfr_ptr -> M7toM4);

   // digitalWrite(LEDB, HIGH);
    Serial.print("Reading M4 to M7, value = "); Serial.println(xfr_ptr -> M4toM7);

    Serial.println("================= End Loop =================");
```



