#ifndef CONFIGS_HPP
#define CONFIGS_HPP
#include <sys/types.h>
#include <iostream>
#include <dirent.h>
#include <chrono>
#include <thread>
#include <random>
#include <string>
#include <vector>
#include <cmath>

//-- Configure According to OS Type by Checking Macros
//- 1 Stands for Windows
//- 2 Stands for Linux (or Unix Based Like MacOS)
//- 3 Stands for MacOS
//- 4 Stands for None-Supported Operating Systems (Like FreeBSD or Android)
extern int16_t osType;
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define DEFAULT_OS 1
    #ifndef _WCTYPE_H
        #include <wctype.h>
    #endif
    #include <windows.h>
#elif defined(unix) || defined(__unix) || defined(__unix__)
    #define DEFAULT_OS 2
    #ifndef _X11_XLIB_H_
        #include <X11/Xlib.h>
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #define DEFAULT_OS 3
#else
    #define DEFAULT_OS 4
#endif

#ifndef OPENCV_HIGHGUI_HPP
    #include <opencv4/opencv2/highgui.hpp>
#endif

#ifndef OPENCV_IMGPROC_HPP
    #include <opencv4/opencv2/imgproc.hpp>
#endif

//-- System Configs (Variable)
//- Screen Resolution
#define DEFAULT_HEIGHT 10
#define DEFAULT_WIDTH 10
struct display {
    int64_t width;
    int64_t height;
};
//-- Modes
#define DEFAULT_MODE 1
//- 1 Stands for Source of Random Generated Dots
//- 2 Stands for Image Source
//- 3 Stands for Webcam Source
extern int16_t mode;

//-- Algorithm
#define DEFAULT_ALGORITHM 1
//- 1 Stands for Graham Scan's Algorithms
//- 2 Stands for Jarvis March's Algorithms
extern int16_t algorithm;
//-- Sort Algorithm
#define DEFAULT_SORT_ALGORITHM 4
//- 1 Stands for Bubble Sort
//- 2 Stands for Quick Sort
//- 3 Stands for Insertion Sort
//- 4 Stands for Selection Sort
//- 5 Stands for Merge Sort
extern int16_t sortAlgorithm;
//-- Treshold Constant Value
#define treshValue 230

//-- Graphics
#define DEFAULT_GRAPHICS true
//- true Will Show How Algorithm Works Step by Step with Aniamtion
//- false Will Show Only Resault
extern bool graphics;
//-- Refresh Time Between Frames (for Video Capturing)
//- in Miliseconds
#define refreshRate 1
//-- Separate Value
extern int64_t separate;
//- Point Size
#define pointSize 1
//- Point Color
#define pointBlue 255
#define pointGreen 240
#define pointRed 113
//- Origin Point Size
#define originSize 5
//- Origin Point Color
#define originBlue 255
#define originGreen 255
#define originRed 255
//- Line Size
#define lineSize 1
//- Line Color
#define lineBlue 137
#define lineGreen 137
#define lineRed 137
//- Font Size
#define fontSize 1
//- Font Color
#define fontBlue 255
#define fontGreen 255;
#define fontRed 255;

//-- Log
#define DEFAULT_TERMINAL 1
//- 1 Stands for Showing Terminal Log
//- 2 Stands for Hiding Terminal Log
extern int16_t terminal;


//-- Points
//- Default Amount
#define DEFAULT_AMOUNT 2000
extern long long int amount;
//- Max Amount
#define max 9000000
//- Min Amount
#define min 3

//-- Window Display
//-- Window Size for Points
#define windowLength 1001
#define windowWidth 1001
//-- Window Size for Frames
#define frameLength 720
#define frameWidth 1080
//-- Window Color
#define windowBlue 13
#define windowGreen 6
#define windowRed 2

#endif // CONFIGS_HPP