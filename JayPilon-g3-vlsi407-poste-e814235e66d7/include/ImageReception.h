#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>


///@brief Changes the resolution when 'a' is pressed
///
///@param length Length of the new resolution
///@param height Height of the new resolution
void ChangeResolution(int& length, int& height);

///@brief Receives the image
///
///@param sock socket connexion to the server
///@param length Length of the new resolution
///@param height Height of the new resolution
///@param image image received
///@param imgSize image size
///@param buffer image data
///@return true if its the last image
///@return false if there are still more images
int ReceiveImage(int &sock, int &length, int &height, cv::Mat& image, int imgSize,std::vector<uchar>& buffer);

///@brief Processes the command received
///
///@param sock socket connexion to the server
///@param key Key pressed
///@param length Length of the new resolution
///@param height Height of the new resolution
///@return true if the user wants to quit
///@return false if the user still wants to continue
bool CommandProcessing (int& sock, int& key, int length, int height );

///@brief Receives the image size
///
///@param sock socket connexion to the server
///@return The image size 
int ImageSize(int sock);

///@brief Saves the image
///
///@param buffer The data of the image
///@param imageCounter counter for the name of the image to save
void  SaveImage(std::vector<uchar>& buffer, int imageCounter);


///@brief Detects if its a rising edge
///
///@param pastState Previous button state
///@param presentState Current button state
///@return true if there's a rising edge
///@return false if it's not a rising edge
bool RisingEdgeDectection(bool pastState, bool presentState);