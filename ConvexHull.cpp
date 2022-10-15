#include "ConvexHull.hpp"

//-- Constructor
ConvexHull::ConvexHull() {
    mode = DEFAULT_MODE;
    algorithm = DEFAULT_ALGORITHM;
    graphics = DEFAULT_GRAPHICS;
    //- Check If Config File is Included or Not
    std::cout << "\033[0;36mChecking Configs Header File ...\033[0m" << std::endl;
    if (checkConfigs()) {
        std::cout << "\033[0;36m- Config Header File \033[0;91mFound\033[0m" << std::endl << std::endl;
        std::cout << "\033[0;36mInitializing Configs ...\033[0m" << std::endl;
        if (initialize()) {
            std::cout << "\033[0;36m- Configuration Done \033[0;91mSuccessfully\033[0m" << std::endl << std::endl;
        } else {
            std::cout << "\033[0;36m- Configuration Done \033[0;31mUnsuccessfully" << std::endl << std::endl;
            exit(0);
        }
    } else {
        std::cout << "\033[0;36m- Config Header File \033[0;31mNot Found\033[0m" << std::endl;
        exit(0);
    }
    //-- Check Mode and Assign Data to Matrix
    if (mode == 1) {
        std::cout << "\033[0;36mGenerating Random Points ...\033[0m" << std::endl;
        if (generateData()) {
            std::cout << "\033[0;36m- \033[0;97m" << amount << "\033[0;36m Points Have been Generated\033[0;91m Successfully\033[0m" << std::endl;
        } else {
            std::cout << "\033[0;36m- Points Generation Was \033[0;31mUnsuccessful\033[0m" << std::endl;
        }
    } else if (mode == 2) {
        if (generateData()) {

        } else {

        }
    } else if (mode == 3) {

    } else {
        std::cout << "\033[0;31mInvalid Mode !\033[0;36m Check Configs Header File\033[0m" << std::endl;
    }
}

//-- Destructor 
ConvexHull::~ConvexHull() {
    //-- Clearing Data
    points.x.clear();
    points.y.clear();
    points.theta.clear();
    convexed.x.clear();
    convexed.y.clear();
    convexed.theta.clear();
    cv::destroyAllWindows();
}

//-- Check If Configs Header File is Included
bool ConvexHull::checkConfigs() noexcept(true) {
    //-- Checks If Configs File is Included or Not
    volatile int16_t status = 0;
    #ifdef CONFIGS_HPP
        status++;
    #endif
    #ifdef OPENCV_HIGHGUI_HPP
        status++;
    #endif
    #ifdef OPENCV_IMGPROC_HPP
        status++;
    #endif
    //-- Return Section
    if (status == 3) {
        return true;
    } else {
        return false;
    }
}

//-- Method to Initialize Program
bool ConvexHull::initialize() noexcept(true) {
    //-- Configuring Output Display Window According to Mode
    if (mode == 1) {
        output = cv::Mat(windowWidth, windowLength, CV_8UC3, cv::Scalar(windowBlue, windowGreen, windowRed));
        // output = cv::imread()
    } else if (mode == 2) {
        //-- Check If Picture is in Folder or Not
        DIR *image;
        image = opendir("Source/");
        struct dirent *action;
        if (image) {
            while ((action = readdir(image)) != NULL) {
                std::string path = action->d_name;
                if (path != "..") {
                    if (path != ".") {
                        path = "Source/" + path;
                        std::cout << "\033[0;36m- Image with The Name \033[0;97m" << action->d_name << "\033[0;36m Has Been \033[0;91mFound\033[0m" << std::endl;
                        output = cv::imread(path, cv::IMREAD_GRAYSCALE);
                    }
                } else {
                    continue;
                }
            }
            closedir(image);
        } else {
            std::cout << "\033[0;36m'Source' Folder \033[0;31mNot Found\033[0m" << std::endl; 
        }
        // std::cout << "\033[0;36mAffecting Filter on Souce Image ...\033[0m" << std::endl;
        // filter();
    } else if (mode == 3) { 

    } else {
        output = cv::Mat(windowWidth, windowLength, CV_8UC3, cv::Scalar(0, 0, 40));
        cv::line(output, cv::Point(0, 0), cv::Point(windowLength, windowWidth), cv::Scalar(0, 0, 190), 10, 8, 0);
        cv::line(output, cv::Point(0, windowWidth), cv::Point(windowLength, 0), cv::Scalar(0, 0, 190), 10, 8, 0);
    }
    //-- Resizing Vectors of Data
    points.x.resize(0);
    points.y.resize(0);
    points.theta.resize(0);
    convexed.x.resize(0);
    convexed.y.resize(0);
    convexed.theta.resize(0);
    //-- Return Section
    if (output.empty() || !points.x.empty() || !points.y.empty() || !points.theta.empty() || !convexed.x.empty() || !convexed.y.empty() || !convexed.theta.empty()) {
        return false;
    } else {
        return true;
    }
}

//-- Generate Points According to Mode
bool ConvexHull::generateData() noexcept(true) {
    amount = 0;
    if (mode == 1) {
        //-- Set Amount of Points That are being Generated
        amount = DEFAULT_AMOUNT; 
        //-- Define Random Points Zone
        struct paddingCNF {
            //-- in Horizontal Axis
            struct horizontalPadding {
                int right;
                int left;
            };
            horizontalPadding horizontal;
            //-- in Vertical Axis
            struct verticalPadding {
                int upper;
                int lower;
            };
            verticalPadding vertical;
        };
        paddingCNF padding;
        padding.horizontal.left = windowLength * 1 / 10;
        padding.horizontal.right = windowLength * 9 / 10;
        padding.vertical.upper = windowWidth * 9 / 10;
        padding.vertical.lower = windowWidth * 1 / 10;
        //-- Creates Engine That Generates Random Numbers
        std::random_device RANDOM;
        std::default_random_engine engine(RANDOM());
        std::uniform_int_distribution <int> distX(padding.horizontal.left, padding.horizontal.right);
        std::uniform_int_distribution <int> distY(padding.vertical.lower, padding.vertical.upper);
        //-- Generating Points
        for (int counter = 0; counter < DEFAULT_AMOUNT; counter++) {
            points.x.push_back(distX(engine));
            points.y.push_back(distY(engine));
            if (graphics) {
                volatile int tmpX = points.x[counter];
                volatile int tmpY = points.y[counter];
                cv::circle(output, cv::Point(tmpX, tmpY), pointSize, cv::Scalar(pointBlue, pointGreen, pointRed), -1, cv::LINE_8, 0);
                cv::imshow("output", output);
            }
            cv::waitKey(1);
        }
        cv::imshow("output", output);
        cv::waitKey(0);
    } else if (mode == 2) {
        
    }
    //-- Return Secton
    if (amount) {
        return true;
    } else {
        return false;
    }
}

//-- Affect Filter to Make Picture Black and White (Working on It...)
void ConvexHull::filter() noexcept(true) {
    // cv::imshow("s", output);
    // cv::waitKey(0);
    // //-- Filter on Horizontal Axis
    // double horizontal[3][3] = {
    //     -3.5, 1, 0,
    //     1, 0, 1,
    //     0, 1, -3.5
    // };
    // //-- Filter on Vertical Axis
    // double vertical[3][3] = {
    //     0, 1, -3.5,
    //     1, 0, 1,
    //     -3.5, 1, 0
    // };
    // volatile double sum = 0;
    // volatile double sumX = 0;
    // volatile double sumY = 0;
    // for (long long int i = 0; i < windowLength; i++) {
    //     for (long long int j = 0; j < windowWidth; j++) {
    //         sumX = 0;
    //         sumY = 0;
    //         for (int p = 0; p < 3; p++) {
    //             for (int q = 0; q < 3; q++) {
    //                 sumX += horizontal[p][q] * output.at<uchar>(p + i, q + j);
    //                 sumY += vertical[p][q] * output.at<uchar>(p + i, q + j);
    //             }
    //         }
    //         sum = sqrt(pow(sumX, 2) + pow(sumY, 2));
    //         if (sum > 255) {
    //             sum = 255;
    //         }
    //         output.at<uchar>(i, j) = sum;
    //         if (i > 0 && j > 0) {
    //             if (output.at<uchar>(i, j) > treshValue) {
    //                 std::cout << "t" << std::endl;
    //                 cv::imshow("output", output);
    //                 cv::waitKey(0);
    //                 output.at<uchar>(i, j) = 255;
    //                 points.x.push_back(i);
    //                 points.y.push_back(j);
    //                 if (graphics) {
    //                     cv::circle(output, cv::Point(points.x[amount], points.y[amount]), pointSize, cv::Scalar(pointBlue, pointGreen, pointRed), -1, cv::LINE_8, 0);
    //                     cv::imshow("output", output);
    //                     cv::waitKey(1);
    //                 }
    //                 if (points.x[amount] == i && points.y[amount] == j) {
    //                     amount++;
    //                 }
    //             }
    //         }
    //     }
    // }
}