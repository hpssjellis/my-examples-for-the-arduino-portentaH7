/*
*  WiFi PNG web save
*  By Jeremy Ellis
*
*/


#include <Arduino.h> // Only needed by https://platformio.org/
#include "WiFi.h"



// Choose either the following arduino_secrets.h tab and bracket out the next 2 lines after it
// That route is more secure.
// Or just change the lines below for your Network and Password. Eaier but not as secure
// Since if you share this file it will have your info on it

//#include "arduino_secrets.h"     // more safe
#define SECRET_SSID ""   // your network
#define SECRET_PASS "" // your password



char ssid[] = SECRET_SSID;    // Changing the secret strings above to a character array
char pass[] = SECRET_PASS;    
int keyIndex = 0;              

int status = WL_IDLE_STATUS;
WiFiServer server(80);


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}











void setup() {
  Serial.begin(115200);      // initialize serial communication
  delay(5000); // time to connect serial
  Serial.println("15 seconds to connect serial monitor if needed");
  delay(5000);
  Serial.println("10 seconds to connect serial monitor if needed");
  delay(5000);
  Serial.println("5 seconds to connect serial monitor if needed");
  delay(5000);
  //while (!Serial);  // blocking call
  
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDR, HIGH);


  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 3 seconds for connection:
    delay(3000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status

   
  // Make a folder if needed
  mkdir("fs/myFolder6",0777);                     // 0777 full access permissions linux style 
  
  
  digitalWrite(LEDR, HIGH); 
  digitalWrite(LEDB, HIGH);  
  digitalWrite(LEDG, LOW); 

}















void myWifi() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    int mode=0;
    int x1 = analogRead(A1);                // read A1
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,

        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor


        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LEDG, HIGH);               // GET /H turns the LED on
          mode=1;
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LEDG, LOW);                // GET /L turns the LED off
            mode=2;
        }

        if (currentLine.endsWith("GET /P")) {
          mode=3;         
          digitalWrite(LEDB, LOW); 
          }
        if (currentLine.endsWith("GET /R")) {
         digitalWrite(LEDB, HIGH); 
         // don't really do anything
         mode=4;
        }

        
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
           //client.println("{answer:42}");
            client.println();


            // the content of the HTTP response follows the header:
            client.print("<input type=button value='LED_BUILTIN Off' onclick='{location=\"/H\"}'>");
            client.print("<input type=button value='LED_BUILTIN On' onclick='{location=\"/L\"}'>");
            
            client.print("<input type=button value='Take Picture' onclick='{location=\"/P\"}'>");
            client.print("<input type=button value='Reset Page' onclick='{location=\"/R\"}'>");
            client.print("<br> AnalogRead(A1); = "+ String(x1)+"<br>" );  


    
             if (mode == 1) {
                 client.print(F("<img src=\"data:image/png;base64,R0lGODdhAQABAPAAAP8AAAAAACwAAAAAAQABAAACAkQBADs=\" />"));
    
             }
    
             if (mode == 2) {
                String cool1 = "R0lGODdhAQABAPAAAP8AAAAAACwAAAAAAQABAAACAkQBADs=";
                client.print("<img src=\"data:image/png;base64," + cool1 + "\" />");
   
             }
    
             if (mode == 3) {
                makePNG();
                
                String cool2 = "aaaaaaaa";
                client.print(F("<img src=\"data:image/png;base64,"));
                client.print(cool2);       
                client.print("\" />");       
  
              }
    
             if (mode == 4) {
        
             }

            // The HTTP response ends with another blank line:
            client.println();    
            // break out of the while loop:    
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

       
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);  
    Serial.println("");
  }
}


void loop(){
   myWifi()
}



