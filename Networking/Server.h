#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>       
#include <sys/socket.h>      
#include <netinet/in.h>      

struct Server {
    int domain;              // Address family (e.g., AF_INET)
    int service;             // Socket type (e.g., SOCK_STREAM)
    int protocol;            // Protocol (usually 0)
    u_long interface;        // IP address to bind to (e.g., INADDR_ANY)
    int port;                // Port number
    int backlog;             // Max number of pending connections

    struct sockaddr_in address; 
    int socket;                
    /*
        struct sockaddr_in {
            short            sin_family;   // e.g. AF_INET
            unsigned short   sin_port;     // e.g. htons(3490)
            struct in_addr   sin_addr;     // IP address
            char             sin_zero[8];  // Padding
        };
    */

    // Pointer to function that takes a Server* and returns void
    void (*launch)(struct Server *server);
};

// Constructor-like function to initialize a Server struct
struct Server server_constructor(
    int domain, int service, int protocol,
    u_long interface, int port, int backlog,
    void (*launch)(struct Server *server)
);

#endif /* SERVER_H */
