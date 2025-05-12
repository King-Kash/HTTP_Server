#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Server server_constructor(int domain, int service, int protocol, 
    u_long interface, int port, int backlog, void (*launch) (struct Server *server))
{
    struct Server server; //declare server

    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);
    
    //socket is how OS communicates with network. It is an endpoint for communication between two machines.
    //service = socket stream (one char after next)
    //gives address for where socket is located
    server.socket = socket(domain, service, protocol);
    if (server.socket < 0) {
        perror("Failed to connect to socket");
        exit(EXIT_FAILURE);
    }

    //binding = associating socket w/ specific IP and port number.
    //like giving name to socket so OS knows what traffic to send to this specifc socket.    
    if (( bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) ) != 0){
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    /*
        creating socket = getting blank phone
        binding socket = register phone number to phone
        one phone associated with phone number the correct incoming calls can be routed to your phone.
    */

    //backlog = line of requests
    if ( listen(server.socket, server.backlog) != 0){
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    server.launch = launch;



    return server;
}