#include "EthernetInterface.h"
EthernetInterface net;
void setup() {  
/* ETH */
  mbed::Watchdog::get_instance().start(10000);  
  int retry_count = 0;
  eth_restart:
  net.set_blocking(false);
  int res = net.connect();
  int start = millis();
  while ((millis() - start < 20000) && (net.get_connection_status() != NSAPI_STATUS_GLOBAL_UP)) {
    delay(10);
    mbed::Watchdog::get_instance().kick();
  }
  if (net.get_connection_status() != NSAPI_STATUS_GLOBAL_UP && retry_count++ < 2) {
    net.disconnect();
    goto eth_restart;
  }
  const char *mac = net.get_mac_address();
  Serial.println("Ethernet MAC" +String(mac));
  SocketAddress addr;
  net.get_ip_address(&addr);
  Serial.println("Ethernet IP" + String(addr.get_ip_address()));}
  void loop() {
  // put your main code here, to run repeatedly:
  }
