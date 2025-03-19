#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

/*
 * Changes the length and the height depending on which resolution the user has decided
 * to change to
 */
void ChangeResolution(int& length, int& height){

    std::cout << "Choisissez de la resolution" << std::endl;
    std::cout << "1. 800 x 600" << std::endl;
    std::cout << "2. 960 x 544" << std::endl;
    std::cout << "3. 1184 x 656" << std::endl;
    std::cout << "4. 320 x 176" << std::endl;
    
    int keyPressResolution;
    std::cin >> keyPressResolution;

    switch (keyPressResolution) {
        case 1: // 800 x 600
        std::cout << "1. 800 x 600" << std::endl;
            length = 800;
            height = 600;
            break;
        case 2: // 960 x 544
        std::cout << "2. 960 x 544" << std::endl;
            length = 960;
            height = 544;
            break;
        case 3: // 1184 x 656
            std::cout << "3. 1184 x 656" << std::endl;
            length = 1184;
            height = 656;
            break;
        case 4: // 320 x 176
            std::cout << "4. 320 x 176" << std::endl;
            length = 320;
            height = 176;
            break;
        default:
            std::cout << "Invalid input. Please choose a valid option." << std::endl;
        }
}

/*
 * Function used to analyse which key has been pressed and sends a char to the server if the user either 
 * wants to change resolution, quit or continue.
 */
bool CommandProcessing (int& sock, int& key, int length, int height) {

    if (key == 97 ) {
        char changeCommand = 'a';
        send(sock, &changeCommand, sizeof(changeCommand), 0);

        ChangeResolution(length, height);
        
        send(sock, &length, sizeof(length), 0);
        send(sock, &height, sizeof(height), 0); 
            
    }
    else if (key == 27) { // ESC key
        char quitCommand = 'q';
        send(sock, &quitCommand, sizeof(quitCommand), 0);
            
        return true;
    } 
    else{
        char continueCommand = 'c';
        send(sock, &continueCommand, sizeof(continueCommand), 0);
    }
    return false;
}

/*
 * Receives the image size used to show the picture on the client window
 */
int ImageSize(int sock){

    int imgSize;
    if (recv(sock, &imgSize, sizeof(imgSize), 0) <= 0) {
        std::cerr << "Failed to receive image size" << std::endl;
        return true;
    }
    return ntohl(imgSize); // Convert to host byte order
}

/* 
 * Saves the image in the current directory using the image data and names it 
 * image[number].png. The variable number incrementes every time this function
 * gets called. 
 */
void  SaveImage(std::vector<uchar>& buffer,int imageCounter){
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    std::string filename = "image" + std::to_string(imageCounter) + ".png";
    cv::imwrite(filename, image);
    std::cout << "Image saved as: " << filename << std::endl;
}

/*
 * Receives the images sent from the server and shows it in a windows on the client. This function
 * returns the ASCII number of a key pressed on the keybaord if the client ever detects a key press.
 */
int ReceiveImage(int &sock, int& length, int& height, cv::Mat& image, int imgSize, std::vector<uchar>& buffer){
    
    // Receive the image data
    int bytes_received = 0;
    while (bytes_received < imgSize) {
        int n = recv(sock, buffer.data() + bytes_received, imgSize - bytes_received, 0);
        if (n <= 0) {
            std::cerr << "Failed to receive image data" << std::endl;
            return true;
        }
        bytes_received += n;
    }

    image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    cv::imshow("Received Image", image);
    int key = cv::waitKey(30);
    return key;
}

/*
 * This function detects if the button is in its rising edge state. 
 */
bool RisingEdgeDectection(bool pastState, bool presentState){
    if (pastState == true && presentState == false){
        return true;
    }
    return false;
}