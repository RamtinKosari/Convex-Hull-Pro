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
    /**
     * @brief Set Data of Points
     * @param _x Default : Half of GDW's Width
     * @param _y Default : Half of GDW's Height
     * @param _z Default : Zero
     * @param _theta Default : Zero
     */
    void Point::setData(
        int _x = GDW_WIDTH / 2,
        int _y = GDW_HEIGHT / 2,
        int _z = 0,
        double _theta = 0
    ) {
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
        //-- Initialize Graphical Visualization
        if (GRAPHICAL_VIEW == true) {
            if (cnf.__SPACE == IN_PLANE) {
                _2D_matrix = cv::Mat (GDW_HEIGHT, GDW_WIDTH, CV_8UC3, cv::Scalar(10, 5, 1));
            } else if (cnf.__SPACE == IN_SPACE) {
                _3D_matrix = cv::viz::Viz3d(GDW_NAME);
            }
        }
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
            std::normal_distribution<double> __dst(
                RANDOM_POINTS_MEAN,
                RANDOM_POINTS_STANDARD_DEVIATION
            );
            //-- Initialize Points Amount
            points.resize(RANDOM_POINTS_AMOUNT);
            //-- Generate Points According to Space
            if (cnf.__SPACE == IN_PLANE) {
                if (GRAPHICAL_VIEW == true) {
                    //-- Generate Points Data
                    for (int i = 0; i < RANDOM_POINTS_AMOUNT; i++) {
                        points[i].setData(__dst(__gen), __dst(__gen));
                        cv::circle(_2D_matrix, cv::Point(points[i].getX(), points[i].getY()), 1, cv::Scalar(255, 255, 0), -1, 8, 0);
                        cv::imshow(GDW_NAME, _2D_matrix);
                        cv::waitKey(1);
                    }
                } else {
                    //-- Generate Points Data
                    for (int i = 0; i < RANDOM_POINTS_AMOUNT; i++) {
                        points[i].setData(__dst(__gen), __dst(__gen));
                    }
                }
            } else if (cnf.__SPACE == IN_SPACE) {
                if (GRAPHICAL_VIEW == true) {
                    std::vector<cv::Point3i> __points;
                    __points.resize(RANDOM_POINTS_AMOUNT);
                    //-- Generate Points Data
                    for (int i = 0; i < RANDOM_POINTS_AMOUNT; i++) {
                        points[i].setData(__dst(__gen), __dst(__gen), __dst(__gen));
                        __points[i].x = points[i].getX();
                        __points[i].y = points[i].getY();
                        __points[i].z = points[i].getZ();
                    }
                    //-- Initialize Cloud with Generated Points
                    cv::viz::WCloud __cloud(__points);
                    //-- Set Points Color
                    __cloud.setColor(cv::viz::Color(255, 0, 0));
                    //-- Add Cloud to Widget
                    _3D_matrix.showWidget(GDW_NAME, __cloud);
                    //-- Start Visualization Loop
                    _3D_matrix.spin();
                } else {
                    //-- Generate Points Data
                    for (int i = 0; i < RANDOM_POINTS_AMOUNT; i++) {
                        points[i].setData(__dst(__gen), __dst(__gen), __dst(__gen));
                    }
                }
            }
            cv::waitKey(0);
            cv::destroyAllWindows();
            std::cout << "t" << std::endl;
        } else if (cnf.__GENERATOR == GENERATE_WITH_DATA) {

        } else if (cnf.__GENERATOR == GENERATE_FROM_FILE) {

        } else if (cnf.__GENERATOR == GENERATE_FROM_IMAGE) {

        } else if (cnf.__GENERATOR == GENERATE_FROM_CAMERA_SOURCE) {

        }
    }
    //-- Method to Generate Points from Data
# endif // __CONVEX_HULL_HPP