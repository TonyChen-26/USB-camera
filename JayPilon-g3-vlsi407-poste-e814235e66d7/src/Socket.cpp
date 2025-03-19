#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


/*
 * Creates a socket connexion with the server using the port. It returns the socket number
 */
int SocketConnexion(int port) {
    int sock;
    struct sockaddr_in server;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.7.2");
    server.sin_port = htons(port);

    // Convert IP address to binary and set server IP
    if (inet_pton(AF_INET, "192.168.7.2", &server.sin_addr) <= 0) { // Replace with Odroid-C2's IP
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return -1;
    }
    std::cout << "Did not connect yet" <<std::endl;
    while (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed" << std::endl;
    }

    std::cout << "Connected to the server on port " << port << std::endl;
    return sock;
}