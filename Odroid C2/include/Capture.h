#pragma once


#include<iostream>
#include<opencv2/opencv.hpp>
#include <chrono>



const static int Width[13]= {176,160,320,320,352,432,800,864,960,960,1184,1280,1280};
const static int Length[13]={144,120,176,240,288,240,600,480,544,720,656,720,960};


/// @brief Calculate the number of pictures per second
/// @param capture Reference to cv::VideoCapture used to create a video
/// @return Number of frames we can capture per second
int ImagesPerSecond(cv::VideoCapture& capture);


/// @brief Creates a video file using pictures taken from the webcam
/// @param Taille Index of a list of resolutions 
void VideoCapture(int Taille);