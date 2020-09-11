



#ifdef CORE_CM4  
void setup() {
}
void loop() { 
}
#endif   // all the M4 core stuff


#ifdef CORE_CM7  

void setup() {  
  pinMode(LEDB, OUTPUT);
  Serial1.begin(115200);
}

void loop() { 
  Serial1.write("This is cool from the M7 core.\r\n");
  digitalWrite(LEDB, LOW);  // flash on-board LED no matter grounding
  delay(2000);
  digitalWrite(LEDB, HIGH);
  delay(2000);    
}

#endif    // all the M7 core stuff
