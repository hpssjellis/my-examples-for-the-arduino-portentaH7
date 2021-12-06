
#include <MKRWAN.h>

LoRaModem modem;

// Uncomment if using the Murata chip as a module
// LoRaModem modem(Serial1);

String appEui = "0";
String appKey = "f936c5f76964b55dee244d4cf469b114";
const int valvola = 0;
const int flussostato = 2;

void setup() {
  pinMode(valvola, OUTPUT);
  pinMode(flussostato, INPUT);

  Serial.begin(115200);
  //while (!Serial);
  Serial.println("Console avviata");
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.print("Errore set modem 868");
    //Lempeggia LED ROSSO VELOCE se il modulo non riesce ad avviarsi
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(300);                       // wait for 300 millisecond
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(300);
    while (1) {}
  };
  Serial.println("Connessione modem effetuata");
  modem.configureClass(CLASS_C);

  int connected;

  appEui.trim();
  appKey.trim();
  Serial.println("Tento la connessione");
  connected = modem.joinOTAA(appEui, appKey);

  if (!connected) {
    Serial.println("NESSUNA CONNESSIONE");
    //Lempeggia LED ROSSO LENTO se il modulo non riesce ad avviarsi
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
    while (1) {}
  }
  Serial.println("Connessione effettuata");


  delay(5000);

  int err;
  modem.setPort(1);
  modem.beginPacket();
  modem.print("Entrato");
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("messaggio inviato");
    //MESSAGGIO INVIATO
    //Lempeggia LED ROSSO leggermente veloce per tre volte
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)      PRIMO LAMPEGGIO
    delay(200);                       // wait for 3 second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)      SECONDO LAMPEGGIO
    delay(200);                       // wait for 3 second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)      TERZO LAMPEGGIO
    delay(200);                       // wait for 3 second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200);
  } else {
    Serial.println("Messaggio NON inviato");
    //MESSAGGIO NON INVIATO
    //RESTA LED ROSSO ACCESO FISSO SE NON COMUNICA
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
}

void loop() {
  delay(1000);
  if (!modem.available()) {
    return;
  } else {
    char rcv[64] = "";
    int i = 0;
    while (modem.available()) {
      rcv[i % 64] = (char)modem.read();
      ++i;
    }

    String messagio = rcv;
    Serial.println(messagio);


    if (messagio == "ON" ) {
      digitalWrite(valvola, HIGH);
      Serial.println("Valvola aperta");

      delay(30000);
      int statoFlussostato = digitalRead(flussostato);
      if (statoFlussostato == HIGH) {
        String msg = "Conferma apertura valvola";
        modem.setPort(1);
        modem.beginPacket();
        modem.print(msg);
        modem.endPacket(true);
      } else {
        String msg = "Errore";
        modem.setPort(1);
        modem.beginPacket();
        modem.print(msg);
        modem.endPacket(true);
      }
    }

    if (messagio == "OFF" ) {
      digitalWrite(valvola, LOW);
      Serial.println("Valvola chiusa");
      delay(30000);
      int statoFlussostato = digitalRead(flussostato);
      if (statoFlussostato == LOW) {
        String msg = "Conferma chiusura valvola";
        modem.setPort(1);
        modem.beginPacket();
        modem.print(msg);
        modem.endPacket(true);
      } else {
        String msg = "Errore";
        modem.setPort(1);
        modem.beginPacket();
        modem.print(msg);
        modem.endPacket(true);
      }
    }
  }
}
