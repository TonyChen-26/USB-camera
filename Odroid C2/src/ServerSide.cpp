#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <vector>

/*
 * Sends an image over a socket connection as JPEG and then receives a character from the client
 * which contains the next server state
 */
char SendMat(int socket, const cv::Mat &image) {
    // Encode the image as a compressed JPEG
    
    std::vector<uchar> buffer;
    cv::imencode(".jpg", image, buffer);
    
    int img_size = htonl(buffer.size());
    send(socket, &img_size, sizeof(int), 0);
    send(socket, buffer.data(), buffer.size(), 0);

    char command;
    recv(socket, &command, sizeof(command),0);
    std::cout << "Received Char: " << command << std::endl;
    return command;
}

/*
 * Creates a socket connexion with the client using the port and the file descriptor
*/
int Tcp(int port, int& server_fd){

    int new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 4099
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR| SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("192.168.7.2"); // Bind to any available network interface
    address.sin_port = htons(port); // Port number

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "Server is listening on port " << port << std::endl;

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "Connection accepted!" << std::endl;

return new_socket;
}

/*
 * Analyses the command sent from the client and returns true if we need to end the connection
 * between the server and the client.
 */
bool End(cv::VideoCapture& capture, int& new_socket, cv::Mat& frame, int length, int height ){

    char commandRetournee = 'c';
    char charRecu;
    
        if (commandRetournee = 'c'){
            capture >> frame;
        }
        commandRetournee= SendMat(new_socket,frame);
        
        if (commandRetournee == 'q') {
            return true;
        } 
        else if (commandRetournee == 'c') {

        }
        else if (commandRetournee == 'a'){
            recv(new_socket,&length,sizeof(length),0);
            recv(new_socket,&height,sizeof(height),0);
        
            capture.set(CV_CAP_PROP_FRAME_WIDTH,length);
            capture.set(CV_CAP_PROP_FRAME_HEIGHT,height);
        }
        return false;
}
