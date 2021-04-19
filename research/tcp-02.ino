/*
 * Dramatically changed by
 * Rocksetta, Jan 28th, 2021
 * 
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "EthernetInterface.h"

// Network interface
EthernetInterface myNet;

// Socket demo
void setup(){

    Serial.begin(115200);

    // so we don't block but allow time to connect the Serial monitor
    delay(5000); 
    
    Serial.println("Starting...");
    Serial.println("Ethernet socket example");
    myNet.connect();
    Serial.println();
    
    // Show the network address
    SocketAddress mySockAddress;
    myNet.get_ip_address(&mySockAddress);
    Serial.println("IP address: " + String(mySockAddress.get_ip_address() ? mySockAddress.get_ip_address() : "None") );
    Serial.println();
    
    // Open a socket on the network interface, and create a TCP connection to mbed.org
    TCPSocket mySocket;
    mySocket.open(&myNet);

    myNet.gethostbyname("ifconfig.io", &mySockAddress);
    mySockAddress.set_port(80);
    mySocket.connect(mySockAddress);
    
    // Send a simple http request
    char sbuffer[] = "GET / HTTP/1.1\r\nHost: ifconfig.io\r\n\r\n";
    int scount = mySocket.send(sbuffer, sizeof sbuffer);
    //printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);
    Serial.println("sent: " +  String(scount) + ", " + String(strstr(sbuffer, "\r\n") - sbuffer)+ ", " + String(sbuffer));
    Serial.println();
    Serial.println();

    // Lets get the webpage   
    char rbuffer[300];
    int rcount;
    while (true) {
        rcount =  mySocket.recv(rbuffer, sizeof(rbuffer)-1); 
        if (rcount <= 0)
            break;
        rbuffer[rcount] = '\0';
       // Serial.println("Received: " + String( ret)+ "chars from server: " + String( strstr(buffer, "\r\n") - buffer)+", "+ String(buffer));
        Serial.println(String(rbuffer));
    }


/*
    int myBufSize = 640;
    // Recieve a simple http response and print out the response line
    //char rbuffer[64];
    char rbuffer[myBufSize];
    int rcount = mySocket.recv(rbuffer, sizeof rbuffer);
    //printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
    Serial.println("recv: " + String( rcount)+ ", " + String( strstr(rbuffer, "\r\n") - rbuffer)+", "+ String(rbuffer));
*/

    // Close the socket to return its memory and bring down the network interface
    mySocket.close();

    // Bring down the ethernet interface
    myNet.disconnect();
    Serial.println("Done.!");
}


void loop(){
  
}
