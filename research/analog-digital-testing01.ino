
void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
 // pinMode(4, OUTPUT); using analogWrite so no pinmode needed
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   
  analogWrite(4, 200);   
  digitalWrite(5, HIGH);  
  digitalWrite(6, HIGH);  
  digitalWrite(7, HIGH);   
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   
  analogWrite(4, 50);    
  digitalWrite(5, LOW);  
  digitalWrite(6, LOW);   
  digitalWrite(7, LOW); 
  delay(4000);                       // wait for 4 seconds
}
