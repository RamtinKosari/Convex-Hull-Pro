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
        __CALCULATION = _clc;
        __ALGORITHM = _alg;
        __GENERATOR = _gen;
        __SPACE = _spc;
    }
    //-- Points Constructor
    Point::Point() {
        y = GDW_HEIGHT / 2;
        x = GDW_WIDTH / 2;
        theta = 0;
    }
    //-- Convex Hull Constructor
    /**
     * @brief Method to Log in-Terminal Messages
     * @param message Input Message to be Logged
     * @param active Prints Log if Logging Messages is Activated in Configuration File
     */
    void logger(const std::string message) {
        if (LOG_MESSAGES) {
            std::cout << LOG << message << std::endl;
        }
    }
# endif // __CONVEX_HULL_HPP