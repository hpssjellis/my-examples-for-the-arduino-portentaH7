
// If uploaded to the M7 Core erases what was on it and boots the M4 core
// If uploaded to the M4 Core erases what was on it.

void setup() {
  #ifdef CORE_CM7  
     bootM4();
  #endif
}

void loop() {
 
}
