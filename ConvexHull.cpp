#include "ConvexHull.hpp"

//-- Constructor
ConvexHull::ConvexHull() {
    mode = DEFAULT_MODE;
    osType = DEFAULT_OS;
    terminal = DEFAULT_TERMINAL;
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
    output = cv::Mat(windowWidth, windowLength, CV_8UC3, cv::Scalar(0, 0, 40));
    //-- Get Screen Size to Put Output Display Window in The Middle of Screen
    display screen;
    if (osType == 1) {
        #if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
            osName = "MS-DOSWindows";
            RECT desktop;
            const HWND hDesktop = GetDesktopWindow();
            GetWindowRect(hDesktop, &desktop);
            screen.height = desktop.right;
            screen.width = desktop.bottom;
        #endif
        //-- Will Work on Later
    } else if (osType == 2 || osType == 3) {
        #if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
            osName = "Unix Based (Linux/MacOS Has Same Configuration Settings)";
            Display* disp = XOpenDisplay(NULL);
            Screen* scrn = DefaultScreenOfDisplay(disp);
            XCloseDisplay(disp);
            screen.height = scrn->height;
            screen.width = scrn->width;
        #endif
    } else if (osType == 4) {
        osName = "Not Supported by This Program";
        std::cout << "\033[0;31mYour Device is Unsupported. Display Window Will be Moved into Default Position\033[0m" << std::endl;
        screen.height = DEFAULT_HEIGHT;
        screen.width = DEFAULT_WIDTH;
    } else {
        osName = "NULL";
        screen.height = DEFAULT_HEIGHT;
        screen.width = DEFAULT_WIDTH;
    }
    //-- Terminal Logger -> Shows Needed System Info
    if (terminal) {
        //- OS Name    
        std::cout << "\033[0;36m- Operating System \033[0m" << osName << std::endl;
        //- Screen Resolution
        std::cout << "\033[0;36m- Screen Resolution \033[0m" << screen.height << " * " << screen.width << std::endl; 
    }
    //-- Move Ouput Window
    volatile int tmpHeight = screen.height / 2 - windowWidth / 2;
    volatile int tmpWidth = screen.width / 2 - windowLength / 2;
    cv::imshow("output", output);
    cv::moveWindow("output", tmpWidth, tmpHeight);    
    // cv::moveWindow("output", 460, 1036);
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
    //-- Configure Separate Value if Graphics is Enabled and Graphics Status Display
    if (graphics) {
        if (amount < 500) {
            separate = 1;
        } else if (amount >= 500 && amount < 1500) {
            separate = 2;
        } else if (amount >= 1250 && amount < 2000) {
            separate = 3;
        } else if (amount >= 2000 && amount < 3500) {
            separate = 4;
        } else {
            separate = 27;
        }
        for (int i = 0; i < 255 * 3; i++) {
            output.copyTo(tmp);
            cv::putText(tmp, "by Ramtin Kosari", cv::Point(windowLength * 7.6 / 20, windowWidth * 5.4 / 10), cv::FONT_HERSHEY_COMPLEX, int(fontSize) / 1.2, cv::Scalar(i / 4, i / 4, i / 4));
            if (i < 255) {
                cv::putText(tmp, "Graphics Has been Enabled", cv::Point(windowLength * 5.4 / 20, windowWidth / 2), cv::FONT_HERSHEY_COMPLEX, fontSize, cv::Scalar(i, i, 0));
            } else if (i >= 255 * 2) {
                cv::putText(tmp, "Graphics Has been Enabled", cv::Point(windowLength * 5.4 / 20, windowWidth / 2), cv::FONT_HERSHEY_COMPLEX, fontSize, cv::Scalar(255 - (i - 255 * 2), 255 - (i - 255 * 2), 0));
                cv::rectangle(tmp, cv::Point(windowLength / 2 - (i - 255 * 2), windowWidth * 5.2 / 10), cv::Point(windowLength / 2 + (i - 255 * 2), windowWidth * 5.6 / 10), cv::Scalar(windowBlue, windowGreen, windowRed), -1, 8, 0);
            } else {
                cv::putText(tmp, "Graphics Has been Enabled", cv::Point(windowLength * 5.4 / 20, windowWidth / 2), cv::FONT_HERSHEY_COMPLEX, fontSize, cv::Scalar(255, 255, 0));
            }
            cv::imshow("output", tmp);
            cv::waitKey(5);
        }
    }
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
        padding.horizontal.left = windowLength * 2 / 10;
        padding.horizontal.right = windowLength * 8 / 10;
        padding.vertical.upper = windowWidth * 8 / 10;
        padding.vertical.lower = windowWidth * 2 / 10;
        //-- Creates Engine That Generates Random Numbers
        std::random_device RANDOM;
        std::default_random_engine engine(RANDOM());
        std::uniform_int_distribution <int> distX(padding.horizontal.left, padding.horizontal.right);
        std::uniform_int_distribution <int> distY(padding.vertical.lower, padding.vertical.upper);
        std::uniform_int_distribution <int> distXCenter(padding.horizontal.left + windowLength * 3.5 / 10, padding.horizontal.right - windowLength * 3.5 / 10);
        std::uniform_int_distribution <int> distYCenter(padding.vertical.lower + windowWidth * 3.5 / 10, padding.vertical.upper - windowWidth * 3.5 / 10);
        // std::uniform_int_distribution <int> distYCenter(30, 90);
        //-- Generating Points
        volatile int tmpX,tmpY;
        volatile int sign = 1;
        output.copyTo(tmp);
        for (int counter = 0; counter < DEFAULT_AMOUNT; counter++) {
            //-- Generates Random Points
            points.x.push_back(distX(engine));
            points.y.push_back(distY(engine));
            //-- Finds Origin Point During Generating Points
            if (points.y[counter] > origin.y) {
                origin.x = points.x[counter];
                origin.y = points.y[counter];
                // if (graphics) {
                //     cv::circle(tmp, cv::Point(origin.x, origin.y), 10, cv::Scalar(0, 255, 0), 1, 8, 0);
                //     cv::line(tmp, cv::Point(origin.x + 3, origin.y + 3), cv::Point(origin.x + 17, origin.y + 15), cv::Scalar(0, 255, 0), 1, 8, 0);
                //     cv::line(tmp, cv::Point(origin.x + 3, origin.y - 3), cv::Point(origin.x + 17, origin.y - 15), cv::Scalar(0, 255, 0), 1, 8, 0);
                //     cv::line(tmp, cv::Point(origin.x - 3, origin.y + 3), cv::Point(origin.x - 17, origin.y + 15), cv::Scalar(0, 255, 0), 1, 8, 0);
                //     cv::line(tmp, cv::Point(origin.x - 3, origin.y - 3), cv::Point(origin.x - 17, origin.y - 15), cv::Scalar(0, 255, 0), 1, 8, 0);
                //     if (counter > 0) {
                //         cv::line(output, cv::Point(origin.x, origin.y), cv::Point(points.x[counter], points.y[counter]), cv::Scalar(255, 255, 255), 1, 8, 0);
                //     }
                // }
            } else {
                output.copyTo(tmp);
            }
            //-- Graphic Section
            if (graphics) {
                tmpX = points.x[counter];
                tmpY = points.y[counter];
                // cv::circle(tmp, cv::Point(tmpX, tmpY), 10, cv::Scalar(255, 255, 255), 1, 8, 0);
                // cv::circle(tmp, cv::Point(tmpX, tmpY), pointSize, cv::Scalar(0, 0, 255), -1, cv::LINE_8, 0);
                cv::circle(output, cv::Point(tmpX, tmpY), pointSize, cv::Scalar(pointBlue / 2, pointGreen / 2, pointRed / 2), -1, cv::LINE_8, 0);
                // cv::line(tmp, cv::Point(tmpX + 3, tmpY + 3), cv::Point(tmpX + 17, tmpY + 15), cv::Scalar(255, 255, 255), 1, 8, 0);
                // cv::line(tmp, cv::Point(tmpX + 3, tmpY - 3), cv::Point(tmpX + 17, tmpY - 15), cv::Scalar(255, 255, 255), 1, 8, 0);
                // cv::line(tmp, cv::Point(tmpX - 3, tmpY + 3), cv::Point(tmpX - 17, tmpY + 15), cv::Scalar(255, 255, 255), 1, 8, 0);
                // cv::line(tmp, cv::Point(tmpX - 3, tmpY - 3), cv::Point(tmpX - 17, tmpY - 15), cv::Scalar(255, 255, 255), 1, 8, 0);
                // cv::circle(tmp, cv::Point(points.x[counter], points.y[counter]), pointSize, cv::Scalar(0, 255, 255), -1, 8, 0);
                cv::imshow("output", output);
            }
            cv::waitKey(1);
        }
        calculateTheta();
        sortPoints();
        if (graphics) {
            cv::imshow("output", output);
            cv::waitKey(0);
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
            output.copyTo(tmp);
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
    //-- Terminal Logger -> Shows Sorted Points
    if (terminal) {
        for (int i = 0; i < amount; i++) {
            std::cout << points.x[i] << " - " << points.y[i] << " - \033[0;93m" << points.theta[i] << "\033[0m" << std::endl;
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
        points.theta.push_back(atan2(origin.y - points.y[i], origin.x - points.x[i]) * 180 / M_PI);
        if (graphics) {
            if (i % separate == 0) {
                cv::imshow("output", tmp);
                cv::waitKey(1);
                output.copyTo(tmp);
            }
            cv::line(tmp, cv::Point(origin.x, origin.y), cv::Point(points.x[i], points.y[i]), cv::Scalar(lineBlue, lineGreen, lineRed), 1, 8, 0);
            cv::circle(output, cv::Point(points.x[i], points.y[i]), pointSize, cv::Scalar(pointBlue, pointGreen, pointRed), -1, 8, 0);
            cv::circle(tmp, cv::Point(points.x[i], points.y[i]), pointSize, cv::Scalar(pointBlue, pointGreen, pointRed), -1, 8, 0);
        }
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
        case 4: {
            selectionSort();
            break;
        }
        default:
            std::cout << "\033[0;31mWrong Sort Algorithm\033[0;36m" << std::endl;
            exit(0);
    }
    if (graphics) {
        for (int i = 0; i < amount; i++) {
            cv::circle(output, cv::Point(points.x[i], points.y[i]), pointSize, cv::Scalar(0, 255, 0), -1, 8, 0);
            cv::imshow("output", output);
            cv::waitKey(1);
        }
    }
}

//-- Bubble Sort Algorithm
void ConvexHull::bubbleSort() noexcept(true) {
    std::cout << "bubble sort" << std::endl;
    volatile int tmpX, tmpY;
    volatile double tmpTheta;
    for (int i = 0; i < amount - 1; i++) {
        for (int j = 0; j < amount - 1; j++) {
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

//-- Quick Sort Algorithm
void ConvexHull::quickSort() noexcept(true) {

}

//-- Insertion Sort Algorithm
void ConvexHull::insertionSort() noexcept(true) {
    std::cout << "insertion sort" << std::endl;
    volatile int tmpX, tmpY, j;
    volatile double tmpTheta;
    for (int i = 1; i < amount; i++) {
        tmpX = points.x[i];
        tmpY = points.y[i];
        tmpTheta = points.theta[i];
        j = i - 1;
        while (points.theta[j] > tmpTheta) {
            points.x[j + 1] = points.x[j];
            points.y[j + 1] = points.y[j];
            points.theta[j + 1] = points.theta[j];
            j--;
        }
        points.x[j + 1] = tmpX;
        points.y[j + 1] = tmpY;
        points.theta[j + 1] = tmpTheta;
    }
}

//-- Selection Sort Algorithm
void ConvexHull::selectionSort() noexcept(true) {
    std::cout << "selection sort" << std::endl;
    volatile int tmpX, tmpY, minimum;
    volatile double tmpTheta;
    for (int i = 0; i < amount - 1; i++) {
        minimum = i;
        for (int j = i + 1; j < amount; j++) {
            if (points.theta[minimum] > points.theta[j]) {
                minimum = j;
            }
        }
        tmpX = points.x[i];
        points.x[i] = points.x[minimum];
        points.x[minimum] = tmpX;
        tmpY = points.y[i];
        points.y[i] = points.y[minimum];
        points.y[minimum] = tmpY;
        tmpTheta = points.theta[i];
        points.theta[i] = points.theta[minimum];
        points.theta[minimum] = tmpTheta;
    }
}

//-- Merge Sort Algorithm
void ConvexHull::mergeSort() noexcept(true) {
    
}

//-- Creates Convex Hull
void ConvexHull::calcConvexHull() noexcept(true) {

}

