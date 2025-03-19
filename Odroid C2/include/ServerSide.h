#pragma once


#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

///@brief Sends the image date to the client
///
///@param socket Connection with the client
///@param image Image to send
///@return char the next state of the server
char SendMat(int socket, const cv::Mat &image);

/// @brief Creates a socket connexion with a client
/// @param port Port of the socket connection
/// @param server_fd File descriptor of the socket
/// @return Reference of the socket of the connexion between the client and the server
int Tcp(int port,int& server_fd);

/// @brief Verifies if data is still being sent
/// @param capture An image capture
/// @param new_socket Connection with the client
/// @param frame Structure for the images
/// @param length Length of the image
/// @param height height of the image
/// @return true if we stop sending data
/// @return false if we keep sending data
bool End(cv::VideoCapture& capture, int& new_socket, cv::Mat& frame, int length, int height );
