// test.c
#include <stdio.h>             // For printf
#include <unistd.h>            // For read(), write(), close()
#include <string.h>            // For strlen()
#include <sys/socket.h>        // For socket(), bind(), listen(), accept()
#include <netinet/in.h>        // For struct sockaddr_in, INADDR_ANY, etc.
#include "Server.h"            // Your own header file that defines struct Server and server_constructor

void launch(struct Server *server) {
    char buffer[30000];
    //res sent to client
    const char *hello =
        "HTTP/1.1 200 OK\r\n"
        "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
        "Server: Apache/2.2.14 (Win32)\r\n"
        "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 37\r\n"
        "Connection: Closed\r\n"
        "\r\n"
        "<html><body><h1>Homo Deus</h1></body></html>";

    while (1) {
        socklen_t address_length = sizeof(server->address);
        printf("\n===== WAITING FOR CONNECTION =====\n");

        int new_socket = accept(
            server->socket,
            (struct sockaddr *)&server->address,
            &address_length
        );
        if (new_socket < 0) {
            perror("accept");
            return;
        }

        //handles properly reading into the buffer by cleaning buffer and performing appropriate checks
        memset(buffer, 0, sizeof buffer);
        ssize_t n = read(new_socket, buffer, sizeof buffer - 1);
        if (n < 0) {
            perror("read");
            close(new_socket);
            return;
        }
        buffer[n] = '\0';

        printf("%s\n", buffer);

        write(new_socket, hello, strlen(hello));
        printf("=== SENDING RESPONSE ===\n%s\n", hello);

        close(new_socket);
    }
}


int main() {
    struct Server server = server_constructor(
        AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch 
    );

    server.launch(&server);
}
