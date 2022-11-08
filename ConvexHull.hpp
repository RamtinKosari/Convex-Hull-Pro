#ifndef CONVEXHULL_HPP
#define CONVEXHULL_HPP
#include "Configs.hpp"

class ConvexHull {
    private:
        //-- Needed Configs
        int16_t mode;
        bool graphics;
        int16_t osType;
        int16_t terminal;
        int16_t separate;
        int16_t algorithm;
        std::string osName;
        int16_t sortAlgorithm;
        //-- Temp Matrix
        cv::Mat tmp;
        //-- Window Matrix
        cv::Mat output;
        //-- Camera Number
        int16_t cameraNumber;
        //-- Structure for Storing Points Data
        struct Data {
            std::vector <long long int> x;
            std::vector <long long int> y;
            std::vector <double> theta;
            int64_t amount;
        };
        Data points;
        //-- Structure for Storing Convexed Hull Points Data
        struct ConvexedData {
            std::vector <int> x;
            std::vector <int> y;
            std::vector <double> theta;
            int64_t amount;
        };
        ConvexedData convexed;
        //-- Structure for Storing Origin Point's Data
        struct originData {
            int x;
            int y;
            int theta;
        };
        originData origin;
    public:
        //-- Constructor
        ConvexHull();
        //-- Destructor
        ~ConvexHull();
        //-- Check If Configs Header File is Included 
        bool checkConfigs() noexcept;
        //-- Method to Initialize Program
        bool initialize() noexcept;
        //-- Generates Points According to Mode
        bool generateData() noexcept;
        //-- Affect Filter to Make Picture or Frame Black and White
        void treshold() noexcept;
        //-- Calculate Angle Theta of Points
        void calculateTheta() noexcept;
        //-- Sort Points by Their Angle Theta from Origin Point
        void sortPoints() noexcept;
        //-- Sort Algorithms
        void bubbleSort() noexcept;
        void quickSort() noexcept;
        void insertionSort() noexcept;
        void selectionSort() noexcept;
        void mergeSort() noexcept;
        //-- Creates ConvexHull According to Selected Algorithm
        //- Graham Scan Algorithm
        void GrahamScan() noexcept;
        //- Jarvis March Algorithm
        void JarvisMarch() noexcept;      
        //- Compare Executation Time of Both Algorithms
        void compare() noexcept;  
        //-- Calculates Determinant of Two Vectors
        int64_t determinant(cv::Point &, cv::Point &, cv::Point &) noexcept;
        //-- Show Result
        void showResult() noexcept;
};

#endif // CONVEXHULL_HPP
