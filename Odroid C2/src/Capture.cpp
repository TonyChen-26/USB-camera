#include<iostream>
#include<opencv2/opencv.hpp>
#include <chrono>

const static int Width[13]= {176,160,320,320,352,432,800,864,960,960,1184,1280,1280};
const static int Height[13]={144,120,176,240,288,240,600,480,544,720,656,720,960};

/*
 * Calculates and returns the average frames per second over a 5 second period
 * by capturing frames from the provided VideoCapture object. Once 5 seconds have
 * passed it returns the number of frames per second calculated by dividing the
 * number of frames captured by 5.
 */
int ImagesPerSecond(cv::VideoCapture& capture){
  int frameCount = 0;
  auto start = std::chrono::high_resolution_clock::now();
  
  cv::Mat frame;
  while (true) {
    frameCount++;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    capture >> frame;


    if (elapsed.count() >= 5.0) { // Every second
      std::cout << "Frames per second: " << frameCount/5 << std::endl;
      break;
    }
  }
  return frameCount/5;
}

/* 
 * Captures video from the default camera and saves it in a file with a specific resolution and
 * frames per second(FPS). The function initializes a video capture with a chosen resolution and with 
 * a FPS calculated using the ImagesPerSecond function. After 5 seconds of video, it saves the video 
 * as 'capture-liv1.avi' using the MJPG codec. 
 */
void VideoCapture(int Taille){
    int fps;
    cv::VideoCapture capture(0);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,Width[Taille]);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,Height[Taille]);
    if(!capture.isOpened()){
	    std::cout << "Failed to connect to the camera." << std::endl;
    }
    
    cv::Mat frame;
    fps = ImagesPerSecond(capture);
    cv::VideoWriter video("capture-liv1.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, 
                          cv::Size(Width[Taille], Height[Taille]));

    for (int i=0; i<fps*5;++i) {
      capture >> frame;
      video.write(frame);
    }

    capture.release();
    video.release();
    cv::destroyAllWindows();
}