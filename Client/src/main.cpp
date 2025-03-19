#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <vector>
#include "Socket.h"
#include <ImageReception.h>
#include <zbar.h>
#include "traitementQR.h"

int main() {
    int sock = SocketConnexion(4099);
    int length = 800;
    int height = 600;
    bool end = false;
    char state;
    int imageSize;
    int key;
    cv::Mat image;

    imageSize = ImageSize(sock);
    std::vector<uchar> buffer(imageSize);
    key  =  ReceiveImage(sock,length,height,image, imageSize, buffer);
    end = CommandProcessing(sock,key,length,height);

    int imageCounter = 0;
    bool pastButtonState;
    bool presentButtonState=false;
    char buttonState;

    //Loop until the user wants to quit
    while (!end) {
        recv(sock, &state,sizeof(state),0);
        std::cout << "Received Char: " << state << std::endl;
        recv(sock, &buttonState, sizeof(buttonState),0);

        pastButtonState = presentButtonState;
        if (buttonState == '1'){
            presentButtonState = true;
        }
        else {
            presentButtonState = false;
        }

        //State where the user pressed the button
        if (state == 'z' ){
            
            imageSize = ImageSize(sock);
            std::vector<uchar> buffer(imageSize);
            key = ReceiveImage(sock,length,height,image, imageSize, buffer);
            CommandProcessing(sock, key, length, height);
            bool risingEdge = RisingEdgeDectection(pastButtonState, presentButtonState);

            if (risingEdge){
                ++imageCounter;
            }

            //Creates the child process for saving the image on the client
            pid_t pid = fork();
            if (pid == 0) {
                std::cout << ("Child process saving Image") << std::endl;
                zbar::Image::SymbolIterator symbol;
                int childConnection = SocketConnexion(4098);
                std::cout << "Socket connection: " << childConnection << std::endl;

                //If the button pressed is a rising edge
                if (risingEdge){
                    SaveImage(buffer, imageCounter);
                    cv::Mat QRimage = cv::imdecode(buffer, cv::IMREAD_COLOR);
                    cv::Mat gray;
                    cv::cvtColor(QRimage, gray, cv::COLOR_BGR2GRAY);
                    zbar::ImageScanner scanner;
                    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);  // Enable all symbologies (QR, barcode, etc.)

                    // Step 4: Create a ZBar image from OpenCV Mat
                    // Create a ZBar Image from the OpenCV Mat (grayscale image)
                    zbar::Image zbarImage(gray.cols, gray.rows, "Y800", gray.data, gray.total());

                    // Step 5: Scan for QR codes or barcodes
                    int n = scanner.scan(zbarImage);  // Scan the image for QR codes/barcodes
                    std::string QRtext;
                    // Step 6: Check if QR codes were found
                    if (n > 0) {
                        // Iterate through detected symbols
                        for (symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol) {
                            // Print the data found in the QR code
                            std::cout << "QR Code found: " << symbol->get_data() << std::endl;
                            for (int i = 0; i < symbol->get_location_size(); ++i) {
                                
                                // Get the coordinates of each point in the bounding box
                                int x = symbol->get_location_x(i);
                                int y = symbol->get_location_y(i);

                                // Draw a red line between consecutive points (i to i+1)
                                cv::line(QRimage, cv::Point(x, y), cv::Point(symbol->get_location_x((i + 1) % symbol->get_location_size()), 
                                                        symbol->get_location_y((i + 1) % symbol->get_location_size())),
                                cv::Scalar(0, 0, 255), 3);  // Red color (BGR) and line thickness 3
                            }
                            QRtext = symbol->get_data();
                        }

                        std::string filename = "QRimage" + std::to_string(imageCounter) + ".png";
                        cv::imwrite(filename, QRimage);

                        
                        std::string filteredText = FilterText(QRtext);
                        std::cout << "Filtered text: "<< filteredText << "\n";
                    
                        //Sending the filtered text to the server
                        char letter;
                        recv(childConnection, &letter, sizeof(char),0);
                        for (size_t i = 0; i < filteredText.length(); ++i ){
                            letter = filteredText[i];
                            send(childConnection, &letter, sizeof(char),0);
                        }
                    } 
                    else {
                        std::cout << "No QR code detected." << std::endl;
                    }
                    char nullChar = '\0';
                     send(childConnection, &nullChar, sizeof(char),0);
                }
                exit(0);
            }
        }
        //Image freezes if there's no light on the photoresistor            
        else if (state == 'n'){
            char freeze = 'n';
            while (freeze == 'n'){
                recv(sock, &freeze, sizeof(freeze),0 );
            }
        }

        else {
            imageSize = ImageSize(sock);
            std::vector<uchar> buffer(imageSize);
            key  =  ReceiveImage(sock,length,height,image, imageSize, buffer);
            end = CommandProcessing(sock,key,length,height);
        }
    }
    char q = 'q';
    send(sock,&q, sizeof(char), 0);
    // Close the socket
    cv::destroyAllWindows();
    close(sock);
    return 0;
}
