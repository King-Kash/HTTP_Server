#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Server
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;
    /*
        struct sockaddr_in {
            short            sin_family;   // e.g. AF_INET
            unsigned short   sin_port;     // e.g. htons(3490)
            struct in_addr   sin_addr;     // IP address
            char             sin_zero[8];  // Padding
        };
    */

    int socket;

    //ptr named launch to function that takes no inputs and returns nothing
    void (*launch) (void);
};

//Function prototype. define existence of function and its params. Implimentation in .c file.
//This function like constructor in C++
struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*launch)(void));


#endif /* Server_h */