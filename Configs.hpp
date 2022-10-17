#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <sys/types.h>
#include <iostream>
#include <dirent.h>
#include <chrono>
#include <thread>
#include <random>
#include <string>
#include <vector>
#include <cmath>

//-- Mode
#define DEFAULT_MODE 2
//- 1 Stands for Source of Random Generated Dots
//- 2 Stands for Image Source
//- 3 Stands for Webcam Source
extern int16_t mode;

//-- Algorithm
#define DEFAULT_ALGORITHM 1
//- 1 Stands for Graham Scan's Algorithms
//- 2 Stands for Jarvis March's Algorithms
extern int16_t algorithm;
//-- Treshold Constant Value
#define treshValue 250

//-- Graphics
#define DEFAULT_GRAPHICS true
//- true Will Show How Algorithm Works Step by Step with Aniamtion
//- false Will Show Only Resault
extern bool graphics;
//- Point Size
#define pointSize 1
//- Point Color
#define pointBlue 255
#define pointGreen 120
#define pointRed 0
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
#define windowLength 500
#define windowWidth 500
//-- Window Size for Frames
#define frameLength 720
#define frameWidth 1080
//-- Window Color
#define windowBlue 13
#define windowGreen 6
#define windowRed 2

#endif // CONFIGS_HPP