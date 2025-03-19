/* boneCV.cpp
 *
 * Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
 * www.derekmolloy.ie
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that source code redistributions retain this notice.
 *
 * This software is provided AS IS and it comes with no warranties of any type. 
 */


#include<iostream>
#include<opencv2/opencv.hpp>
#include <chrono>
#include "Capture.h"
#include "ServerSide.h"
#include "OdroidState.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "QRProcessing.h"

int main()
{
    int serverFd;
    int sock = Tcp(4099, serverFd); 
    ActivateButton();
    cv::VideoCapture capture(0);
    bool endLoop = false;
    cv::Mat frame;
    int length = 800;
    int height = 600;

    capture.set(CV_CAP_PROP_FRAME_WIDTH,length);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,height);
    char state;
    End(capture,sock, frame, length, height);
    bool buttonState;
    char _true = '1';
    char _false = '0';

    system("modprobe pwm-meson");
    system("modprobe pwm-ctrl");

    //Loops until the user wants to quit
    while (!endLoop) {

        buttonState=ButtonState();
        state = StateMachine(ReadVoltage(),buttonState);
        send(sock,&state, sizeof(state),0);

        if (buttonState == true){
            send(sock, &_true, sizeof(_true),0);
        }
        else {
            send(sock, &_false, sizeof(_false),0);
        }

        //If the user wants to take a picture
        if (state == 'z' ){
            endLoop = End(capture,sock, frame, length, height);

            pid_t pid = fork();
            //Child process for the QR text
            if (pid == 0 ){
                close(serverFd);
                close(sock);

                int childSocket; 
                int connexionChild = Tcp(4098,childSocket);
                std::string QRtext="";
                char caractere = 'B';
                send(connexionChild, &caractere, sizeof(char),0);

                //Used to receive the filtered QR text from the client
                while (true){
                    recv(connexionChild, &caractere, sizeof(char),0);
                    QRtext.push_back(caractere);
                    if (caractere == '\0'){
                        break;
                    }
                }

                //We play the morse code on the buzzer if QR text isn't null
                if (static_cast<int>(QRtext[0])!= 0 && QRtext.length() != 1 ){
                    PlayMorse(QRtext);
                    std::cout << "Received Code: " <<QRtext << std::endl;
                }

                close(childSocket);
                close(connexionChild);
                exit(0);
            }
        }

        //If there isn't any light detected on the photoresistor     
        else if (state == 'n'){
            char newState;
            while (state == 'n'){
                send(sock, &state, sizeof(state), 0);
                newState = StateMachine(ReadVoltage(),ButtonState());
                if (newState != 'n'){
                    send(sock,&newState, sizeof(newState), 0);
                    break;
                }
            }
        }
        else {
        endLoop = End(capture,sock, frame, length, height);
        }
    }
    close(serverFd);
    close(sock);
    return 0;
}