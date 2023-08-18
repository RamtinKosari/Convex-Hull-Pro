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
    //-- Convex Hull Constructor
    ConvexHull::ConvexHull(Configuration __input_config) {
        cnf = __input_config;
        isAutomatic = false;
    }
# endif // __CONVEX_HULL_HPP