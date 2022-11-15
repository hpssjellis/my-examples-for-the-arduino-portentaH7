/******  WIFI  *******/
#include <WiFi.h>
char ssid[] = "";    // your network SSID (name)
char pass[] = "";   // your network password (use for WPA, or use as key for WEP)
#define  Serial  _UART_USB_

int keyIndex = 0;             // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
WiFiServer server(80);

/*** BUFFER******/
#include <SDRAM.h>
SDRAMClass mySDRAM;
int j = 0; int k = 0; float freq;
float *a, *b, *c,  *e; int *d, *f;
float a2, b2, c2, e2; int d2, f2;
unsigned long timezero, timefin;

/**************ORDERS*******/
int mode = 0;
int pause;





void setup() {

  /****  COMMUNICATION  ****/
  _UART_USB_ .begin(115200);
  delay(5000);
  //  _UART_USB_.println("20 second delay to attach serial monitor, if you want");
  //  delay(20000);
  _UART_USB_.println("Now starting");
  //while (!_UART_USB_);  // don't do this or it does not work when serial disconnected





  /****  SETUP WIFI  ****/
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDR, HIGH);
  // by default the local IP address of will be 192.168.3.1
  // you can override it with the following:
  // WiFi.config(IPAddress(10, 0, 0, 1));
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    _UART_USB_ .print("Attempting to connect to SSID: ");
    _UART_USB_ .println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 4 seconds for connection:
    delay(4000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();


  /****RAM******/
  mySDRAM.begin(SDRAM_START_ADDRESS);
  a = (float*)SDRAM.malloc(1000000);
  b = (float*)SDRAM.malloc(1000000);
  c = (float*)SDRAM.malloc(1000000);

  delay(2000);

}

void loop() {

  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      _UART_USB_ .println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      _UART_USB_ .println("Device disconnected from AP");
    }
  }

  WiFiClient client = server.available();   // listen for incoming clients

  if (client)
  { // if you get a client,
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      { // if there's bytes to read from the client,

        String currentLine = client.readStringUntil('\n');

        if (currentLine.indexOf("GET /WON") > -1)
        {
          digitalWrite(LEDR, HIGH);
          digitalWrite(LEDG, HIGH);
          digitalWrite(LEDB, LOW);
          _UART_USB_ .println("ON");
          //client.println("ON");
          timezero = millis();
          mode = 1;
        }
        else if (currentLine.indexOf("GET /WOFF") > -1)
        {
          digitalWrite(LEDR, HIGH);
          digitalWrite(LEDG, HIGH);
          digitalWrite(LEDB, HIGH);
          _UART_USB_ .println("OFF");
          //client.println("OFF");
          mode = 2;
          timefin = millis();
        }
 

        sendHeader(client);
        client.print("<input type=button value='Start Recording Data' onclick='{location=\"/WON\"}'>");
        client.print("<input type=button value='Stop Recording Data' onclick='{location=\"/WOFF\"}'>");
       
        client.print(F("<html>\n"));
        client.print(F("<head>\n"));
        client.print(F("<script>\n"));
        client.print(F("function saveFileAs() {\n"));
        client.print(F("var myFilename01 = document.getElementById('myText01').value + '.txt';\n"));
        client.print(F("var myTextBlob = new Blob([document.getElementById('myTextarea01').value], {type:'text/plain'});\n"));
        client.print(F("var myDownloadLink = document.createElement('a');\n"));
        client.print(F("myDownloadLink.download = myFilename01;\n"));
        client.print(F("myDownloadLink.innerHTML = 'Download File';\n"));
        client.print(F("myDownloadLink.href = window.URL.createObjectURL(myTextBlob);\n"));
        client.print(F("myDownloadLink.click();\n"));
        client.print(F("delete myDownloadLink;\n"));
        client.print(F("delete myTextBlob;\n"));
        client.print(F("}\n"));
        client.print(F("</script>\n"));
        client.print(F("</head>\n"));
        client.print(F("<body>\n"));
        client.print(F("<form id=\"myForm01\" target=\"_blank\" method=\"POST\">"));
        client.print(F("<input type=text id=\"myText01\" value=\"test1\"><br>\n"));
        client.print(F("<textarea id=\"myTextarea01\" rows=5 cols=70 >"));
        
        for (k = 0; k <= j - 1; k++)
        {
          client.print(a[k]); client.print(",");
          client.print(b[k]); client.print(",");
          client.println(c[k]);
        }

        client.print(F("</textarea><br>\n"));
        client.print(F("<input type=button value=\"Save text as file\" onclick=\"{saveFileAs();}\">\n"));
        client.print(F("</form>\n"));
        client.print(F("</body>\n"));
        client.print(F("</html>\n"));
        
        // Svuota il myarray in ricezione di client.
        while (client.available()) client.read();
        client.flush();
        break;
      } // end if (client.available())
    } // end while (client.connected())
    client.stop();

  } // end if (client)

  if (mode == 2) {         /****print data*****/
    mode = 0; delay(1000);
    freq = j / ((timefin - timezero) / 1000);
    _UART_USB_ .print(j); _UART_USB_ .print(" samples in  "); _UART_USB_ .print(timefin - timezero); _UART_USB_ .println(" ms");
    _UART_USB_ .print("Frequency: "); _UART_USB_ .print(freq); _UART_USB_ .println(" Hz");
    j = 0;
  }

  else if (mode == 1) {  /*****SAVE IN RAM*****/
    a2 = 1 + j; b2 = 2 + j; c2 = 3 + j;
    a[j] = 1 + j; b[j] = 2 + j; c[j] = 3 + j;
    _UART_USB_ .print("a: "); _UART_USB_ .print(a[j]);  _UART_USB_ .print(" , ");
    _UART_USB_ .print("b: "); _UART_USB_ .print(b[j]);  _UART_USB_ .print(" , ");
    _UART_USB_ .print("c: "); _UART_USB_ .println(c[j]);
    j = j + 1;
    delay(400);
  }

 

} //end loop


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  _UART_USB_ .print("SSID: ");
  _UART_USB_ .println(WiFi.SSID());
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  _UART_USB_ .print("IP Address: ");
  _UART_USB_ .println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  _UART_USB_ .print("signal strength (RSSI):");
  _UART_USB_ .print(rssi);
  _UART_USB_ .println(" dBm");
}

void sendHeader(WiFiClient & locClient) {
  locClient.println("HTTP/1.1 200 OK");
  locClient.println("Content-Type: text/html");
  locClient.println("Connection: close");
  locClient.println();
}
