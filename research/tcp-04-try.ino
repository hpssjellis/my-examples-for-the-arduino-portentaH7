#include "mbed.h"
#include "EthernetInterface.h"
//#include "TCPServer.h" // not needed anymore
//#include "TCPSocket.h" // not needed anymore
 
int main()
{
    printf("TCP server example\n");
    
    EthernetInterface eth;
    eth.connect();
    
  //  printf("The Server IP address is '%s'\n", eth.get_ip_address());
    
    //TCPServer srv;  //TCPServer was migrate to TCPSocket
    TCPSocket srv;
    TCPSocket *client_sock;  // srv.accept() will return pointer to socket
    SocketAddress client_addr;
    char *buffer = new char[256];
    
    /* Open the server on ethernet stack */
    srv.open(&eth);
    
    /* Bind the HTTP port (TCP 80) to the server */
   // srv.bind(eth.get_ip_address(), 23);
    
    /* Can handle x simultaneous connections */
    srv.listen(1);
 
    client_sock = srv.accept();  //return pointer of a client socket
    client_sock->getpeername(&client_addr);  //this will fill address of client to the SocketAddress object
    printf("Accepted %s:%d\n", client_addr.get_ip_address(), client_addr.get_port());
    strcpy(buffer, "Hello \n\r");
    client_sock->send(buffer, strlen(buffer));
    client_sock->recv(buffer, 256);
    printf("Received Msg: %s\n", buffer);  //this was missing in original example. 
    client_sock->close();
    delete[] buffer;
}
