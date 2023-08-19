# ifndef __CONVEX_HULL_HPP
    # include "ConvexHull.hpp"
    /**
     * @brief Constructor that Sets Convex Hull's Configuration
     */
    bool Configuration::set(
        int _clc = CALC_SPEED_DETAILS,
        int _gen = GENERATE_WITH_DATA,
        int _alg = GRAHAM_SCAN,
        int _spc = IN_PLANE
    ) {
        std::cout << LOG "Initializing Configuration" ENDL;
        //-- Check if Selected Generator Method is Correct
        if (_gen <= -1 && _gen >= -5) {
            __GENERATOR = _gen;
            std::cout << TAB SUCCESS "Generator Method has been Configured" ENDL;
        } else {
            std::cout << TAB FAILED "Generator Method is Invalid" ENDL;
            return false;
        }
        //-- Check if Selected Calculation Speed Method is Correct
        if (_clc <= -6 && _clc >= -9) {
            if (GRAPHICAL_VIEW != true) {
                std::cout << TAB WARNING "Graphical View is Not Avalible Due to Configuration" ENDL;
                __CALCULATION = CALC_SPEED_ULTRA;
                std::cout << TAB TAB SUCCESS "CALC_SPEED_ULTRA has been Set Instead" ENDL;
            } else {
                __CALCULATION = _clc;
                std::cout << TAB SUCCESS "Calculation Speed Method has been Configured" ENDL;
            }
        } else {
            std::cout << TAB FAILED "Calculation Speed Method is Invalid" ENDL;
            return false;
        }
        //-- Check if Selected Algorithm is Correct
        if (_alg >= 0 && _alg <=7) {
            __ALGORITHM = _alg;
            std::cout << TAB SUCCESS "Convex Hull Algorithm has been Configured" ENDL;
        } else {
            std::cout << TAB FAILED "Convex Hull Algorithm is Invalid" ENDL;
            return false;
        }
        //-- Check if Selected Space is Correct
        if (_spc >= 8 && _spc <= 9) {
            __SPACE = _spc;
            std::cout << TAB SUCCESS "Mathematical Space has been Configured" ENDL;
        } else {
            std::cout << TAB FAILED "Mathematical Space is Invalid" ENDL;
            return false;
        }
        return true;
    }
    //-- Points Constructor
    Point::Point() {
        y = GDW_HEIGHT / 2;
        x = GDW_WIDTH / 2;
        theta = 0;
        z = 0;
    }
    //-- Set Data of Points
    void Point::setData(int& _x, int& _y, int& _z, double& _theta) {
        theta = _theta;
        x = _x;
        y = _y;
        z = _z;
    }
    //-- Convex Hull Constructor
    ConvexHull::ConvexHull(Configuration __input_config) {
        cnf = __input_config;
        isAutomatic = false;
        points.resize(0);
    }
    //-- Automatic Processing Convex Hull Method
    bool ConvexHull::automatic() {
        //-- Load Points Data
        loadPointsData();
        return true;
    }
    //-- Method to Load Points Data
    bool ConvexHull::loadPointsData() {
        if (cnf.__GENERATOR == GENERATE_RANDOM) {
            //-- Seed Random Generator
            std::random_device __rnd;
            //-- Mersenne Twister PRNG
            std::mt19937 __gen(__rnd());
            // Create a Normal Distribution with the Given Mean and Standard Deviation
            std::normal_distribution<double> distribution(
                RANDOM_POINTS_MEAN,
                RANDOM_POINTS_STANDARD_DEVIATION
            );
            //-- Initialize Points Amount
            points.resize(RANDOM_POINTS_AMOUNT);
            cv::Mat tmp(GDW_HEIGHT, GDW_WIDTH, CV_8UC3, cv::Scalar(10, 10, 10));
            for (int i = 0; i < RANDOM_POINTS_AMOUNT; i++) {
                cv::circle(tmp, cv::Point(distribution(__gen), distribution(__gen)), 1, cv::Scalar(255, 255, 0), -1, 8, 0);
                cv::imshow("t", tmp);
                cv::waitKey(1);
                // std::cout << "Random Number " << i + 1 << ": " << random_value << std::endl;
            }
            // cv::imshow("t", tmp);
            cv::waitKey(0);
            cv::destroyAllWindows();
        } else if (cnf.__GENERATOR == GENERATE_WITH_DATA) {

        } else if (cnf.__GENERATOR == GENERATE_FROM_FILE) {

        } else if (cnf.__GENERATOR == GENERATE_FROM_IMAGE) {

        } else if (cnf.__GENERATOR == GENERATE_FROM_CAMERA_SOURCE) {

        }
    }
    //-- Method to Generate Points from Data
# endif // __CONVEX_HULL_HPP