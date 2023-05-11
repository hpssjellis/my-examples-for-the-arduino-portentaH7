void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

}

void loop() {
  while (Serial1.available()){
    char myIn = Serial1.read();
    if (myIn == 0x54) {
      Serial.println();
      Serial.print("Start: ");
      Serial.print(myIn, HEX);
    } else {
      Serial.print(" ");
      if (myIn <= 15 ){Serial.print(" ");} // add a space for single digit hex values
      Serial.print(myIn, HEX);
  }

  }

}


/*

Bytes: header, length, speed(2), start-angle(2),Data(max 12x3),end-angle(2),timestamp(2),CRC
6 bytes, then data, then 5 bytes

Start: 54 2C 69  8 B8 72 93  0 E6 93  0 E6 92  0 E6 92  0 E8 91  0 E8 91  0 E4 91  0 E6 90  0 E8 90  0 90  0 90  0 8F  0 A3 76 9D 6A
Start: 54 2C 69  8  5 77 8F  0 E6 8F  0 E6 8F  0 E8 8F  0 E6 8F  0 E6 8F  0 E4 8F  0 E8 8F  0 E8 8F  0 E6 90  0 EA  0 E4 90  0 F3 7A A2 DB
Start: 54 2C 69  8 4E 7B 90  0 E6 91  0 E4 91  0 EA 92  0 E8 92  0 E4 93  0 E6 93  0 E8 94  0 E6 94  0 E4 95  0 E6 96  0 E6 97 E4 3F A7 14 55
Start: 54 2C 6D  8 9A 7F 98  0 E4 98  0 E4 99  0 E4 9A  0 E6 9B  0 E4 9C  0 E4 9E  0 E4 9E  0 E4 A0  0 E4  0 E4 A2  0 E2 E4 8B 83 14 16
Start: 54 2C 6D  8 E8 83 A5  0 E2 A6  0 E2 A7  0 E2 A9  0 E0 AB  0 E2 AD  0 E0 AE  0 B0  0 E2  0 E4 B4 E2 B6 E2 B8  0 E4 D2 B1 14 3B
Start: 54 2C 68  8 2D 88 BA  0 E2 BD  0 E2 BF  0 E2 C1  0 E0 C4  0 E2 C7  0 E0 CA  0 E2 CC  0 E0 CF  0 E0  0 E0  0 E4 D9  0 E2 8C B6 A9
Start: 54 2C 72  8 7C 8C DC  0 E0 E0  0 E0 E4  0 E0 E9  0 E2 EC  0 E0 F1  0 E0 F5  0 E0 FA  0 E0 FF  0 E2  4  1  A  1 E4  7  1 CF  3 BB 29
Start: 54 2C 72  8 2B  4  5  1 E4  2  1 E4 FF  0 E4 FD  0 E6 FB  0 E8 F9  0 E6 F6  0 E6 F4  0 E6  0 E6  0 E6 F0 E8 EF  0 E4  8 C0 14
Start: 54 2C 71  8 7E  8 ED  0 E6 EC  0 E4 EB  0 E4 EA  0 E8 E9  0 EA E8  0 E8 E7  0 E6 E5  0 E8 E5  0 EA E5  0 E4 E4  0 E3  0 E8 70  C 14 C0
Start: 54 2C 70  8 CB  C E2  0 E8 E2  0 E8 E2  0 E8 E1  0 E8 E1  0 E8 E1  0 EA E1  0 E8 E1  0 E8 E1  0 EA E1 E6 E0  0 E8 E0 EA BB CB 14 32


*/
