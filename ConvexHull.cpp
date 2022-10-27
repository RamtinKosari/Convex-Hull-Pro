#include "ConvexHull.hpp"

//-- Constructor
ConvexHull::ConvexHull() {
    mode = DEFAULT_MODE;
    graphics = DEFAULT_GRAPHICS;
    algorithm = DEFAULT_ALGORITHM;
    sortAlgorithm = DEFAULT_SORT_ALGORITHM;
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
        std::cout << "\033[0;36mGenerating Points from Source Picture ...\033[0m" << std::endl;
        if (generateData()) {
            std::cout << "\033[0;36m- \033[0;97m" << amount << "\033[0;36m Points Have been Generated\033[0;91m Successfully\033[0m" << std::endl;
        } else {
            std::cout << "\033[0;36m- Points Generation Was \033[0;31mUnsuccessful\033[0m" << std::endl;
        }

    } else if (mode == 3) {
        std::cout << "\033[0;36mGenerating Points from Video Frames\033[0m" << std::endl;
        if (generateData()) {
            std::cout << "\033[0;36m- \033[0;97m" << amount << "\033[0;36m Points Have been Generated\033[0;91m Successfully\033[0m" << std::endl;
        } else {
            std::cout << "\033[0;36m- Points Generation Was \033[0;31mUnsuccessful\033[0m" << std::endl;
        }
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
    cv::waitKey(0);
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
    bool status = false;
    if (mode == 1) {
        output = cv::Mat(windowWidth, windowLength, CV_8UC3, cv::Scalar(windowBlue, windowGreen, windowRed));
        if (!output.empty()) {
            status = true;
        }
    } else if (mode == 2) {
        //-- Check If Picture is in Folder or Not
        DIR *image;
        image = opendir("Source/");
        struct dirent *action;
        if (image) {
            //-- Opens any Image That is in Source Folder
            while ((action = readdir(image)) != NULL) {
                std::string path = action->d_name;
                if (path != "..") {
                    if (path != ".") {
                        path = "Source/" + path;
                        std::cout << "\033[0;36m- Image with The Name \033[0;97m" << action->d_name << "\033[0;36m Has Been \033[0;91mFound\033[0m" << std::endl;
                        output = cv::imread(path, cv::IMREAD_GRAYSCALE);
                        cv::resize(output, output,cv::Size(frameWidth, frameLength));
                        status = true;
                    }
                } else {
                    continue;
                }
            }
            closedir(image);
        } else {
            std::cout << "\033[0;36m'Source' Folder \033[0;31mNot Found\033[0m" << std::endl; 
        }
    } else if (mode == 3) { 
        for (int i = -2; i < 2; i++) {
            cv::VideoCapture capture(i);
            if (capture.isOpened()) {
                std::cout << "\033[0;36m- Camera Source \033[0;91mFound\033[0m" << std::endl;
                cameraNumber = i;
                status = true;
                break;
            }
        }
        if (!status) {
            std::cout << "\033[0;36m- Camera Source \033[0;31mNot Found\033[0m" << std::endl;
        }
    } else {
        output = cv::Mat(windowWidth, windowLength, CV_8UC3, cv::Scalar(0, 0, 40));
        cv::line(output, cv::Point(0, 0), cv::Point(windowLength, windowWidth), cv::Scalar(0, 0, 190), 10, 8, 0);
        cv::line(output, cv::Point(0, windowWidth), cv::Point(windowLength, 0), cv::Scalar(0, 0, 190), 10, 8, 0);
        cv::imshow("output", output);
        cv::waitKey(0);
    }
    //-- Resizing Vectors of Data
    points.x.resize(0);
    points.y.resize(0);
    points.theta.resize(0);
    convexed.x.resize(0);
    convexed.y.resize(0);
    convexed.theta.resize(0);
    origin.x = 0;
    origin.y = 0;
    //-- Return Section
    if (status) {
        return true;
    } else {
        return false;
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
            //-- Finds Origin Point During Generating Points
            if (points.y[counter] > origin.y) {
                origin.x = points.x[counter];
                origin.y = points.y[counter];
            }
            if (graphics) {
                volatile int tmpX = points.x[counter];
                volatile int tmpY = points.y[counter];
                cv::circle(output, cv::Point(tmpX, tmpY), pointSize, cv::Scalar(pointBlue, pointGreen, pointRed), -1, cv::LINE_8, 0);
                cv::imshow("output", output);
            }
            cv::waitKey(1);
        }
        calculateTheta();
        sortPoints();
        for (int i = 0; i < amount; i++) {
            std::cout << points.x[i] << " - " << points.y[i] << " - \033[0;93m" << points.theta[i] << "\033[0m" << std::endl;
        }
        if (graphics) {
            cv::imshow("output", output);
            cv::waitKey(2000);
        }
    } else if (mode == 2) {
        treshold();
        calculateTheta();
        if (graphics) {
            cv::imshow("output", output);
            cv::waitKey(2000);
        }
    } else if (mode == 3) {
        cv::VideoCapture capture(cameraNumber);
        while (true) {
            amount = 0;
            capture >> output;
            cv::cvtColor(output, output, cv::COLOR_BGR2GRAY);
            cv::resize(output, output,cv::Size(frameWidth, frameLength));
            switch (cv::waitKey(1)) {
                case (int('q')):{
                    std::cout << "\033[0;97mTerminated \033[0;31mSuccessfully\033[0m" << std::endl;
                    exit(0);
                    break;
                }
                case (int('p')): {
                    std::cout << "\033[0;36m- Pause\033[0m" << std::endl; 
                    if (cv::waitKey(0) == int('r')) {
                        std::cout << "\033[0;36m- Resume\033[0m" << std::endl;
                        continue;
                    } 
                    break;
                }
            }
            treshold();
            calculateTheta();
            if (graphics) {
                cv::imshow("output", output);
                cv::waitKey(refreshRate);
            }
        }
    }
    //-- Return Secton
    if (amount) {
        return true;
    } else {
        return false;
    }
}

//-- Affect Filter to Make Picture or Frame Black and White
void ConvexHull::treshold() noexcept(true) {
    volatile int tmpX;
    volatile int tmpY;
    for (int i = 0; i < output.rows; i++) {
        for (int j = 0; j < output.cols; j++) {
            if (output.at<uchar>(i, j) < treshValue) {
                output.at<uchar>(i, j) = 0;
            } else {
                output.at<uchar>(i, j) = 255;
                tmpX = j;
                tmpY = i;
                points.x.push_back(tmpX);
                points.y.push_back(tmpY);
                //-- Finds Origin Point During Generating Points
                if (points.y[amount] > origin.y) {
                    origin.x = tmpX;
                    origin.y = tmpY;
                }
                amount++;
                if (graphics) {
                    if (j % 15 == 0) {
                        cv::imshow("output", output);
                        cv::waitKey(1);
                    }
                }
            }
        }
    }
}

//-- Calculate Angle Theta of Points
void ConvexHull::calculateTheta() noexcept(true) {
    for (int i = 0; i < amount; i++) {
        points.theta.push_back(atan2(origin.y - points.y[i], origin.x - points.x[i]));
    }
}

//-- Sort Points by Their Angle Theta from Origin Point
void ConvexHull::sortPoints() noexcept(true) {
    switch (sortAlgorithm) {
        case 1: {
            bubbleSort();
            break;
        }
        case 2: {
            quickSort();
            break;
        }
        case 3: {
            insertionSort();
            break;
        }
    }
}

//-- Bubble Sort Algorithm
void ConvexHull::bubbleSort() noexcept(true) {
    volatile int tmpX, tmpY, tmpTheta;
    cv::Mat tmp;
    output.copyTo(tmp);
    for (int i = 0; i < amount; i++) {
        for (int j = 0; j < amount; j++) {
            if (points.theta[j] > points.theta[j + 1]) {
                tmpX = points.x[j + 1];
                points.x[j + 1] = points.x[j];
                points.x[j] = tmpX;
                tmpY = points.y[j + 1];
                points.y[j + 1] = points.y[j];
                points.y[j] = tmpY;
                tmpTheta = points.theta[j + 1];
                points.theta[j + 1] = points.theta[j];
                points.theta[j] = tmpTheta;
            }
        }
    }
}

//-- Insertion Sort Algorithm
void ConvexHull::insertionSort() noexcept(true) {
    volatile int tmp;
    for (int i = 1, j; i < points.theta.size(); i++) {
        tmp = points.theta[i];
        j = tmp - 1;
        while (tmp < points.x[j] && j >= 0) {
            points.theta[j + 1] = points.theta[j];
            --j;
        }
        points.theta[j + 1] = tmp;
    }
    for (int i = 0; i < amount; i++) {
        std::cout << points.x[i] << " - " << points.y[i] << std::endl;
    }
}

void ConvexHull::quickSort() noexcept(true) {

}

//-- Creates Convex Hull
void ConvexHull::calcConvexHull() noexcept(true) {

}

//-- Creates ConvexHull
// long int ConvexHull::determinant(int xSelected, int ySelected, int xLast, int yLast, int xBeforeLast, int yBeforeLast) noexcept(true) {

// }

