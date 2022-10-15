#ifndef CONVEXHULL_HPP
#define CONVEXHULL_HPP
#include "Configs.hpp"

class ConvexHull {
    private:
        //-- Needed Configs
        int16_t mode;
        int16_t algorithm;
        bool graphics;
        long long int amount;
        //-- Window Mat
        cv::Mat output;
        //-- Structure for Storing Points Data
        struct Data {
            std::vector <int> x;
            std::vector <int> y;
            std::vector <double> theta;
        };
        Data points;
        //-- Structure for Storing Convexed Hull Points
        struct ConvexedData {
            std::vector <int> x;
            std::vector <int> y;
            std::vector <double> theta;
        };
        ConvexedData convexed;
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
        //-- Affect Filter to Make Picture Black and White
        void filter() noexcept;
};

#endif // CONVEXHULL_HPP