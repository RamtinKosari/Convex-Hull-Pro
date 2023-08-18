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
        //-- Check if Selected Generator Method is Correct
        if (_gen <= -1 && _gen >= -5) {
            __GENERATOR = _gen;
        } else {
            std::cout << FAILED "Generator Method is Invalid" ENDL;
        }
        //-- Check if Selected Calculation Speed Method is Correct
        if (_clc <= -6 && _clc >= -9) {
            __CALCULATION = _clc;
        } else {
            std::cout << FAILED "Calculation Speed Method is Invalid" ENDL;
        }
        //-- Check if Selected Algorithm is Correct
        if (_alg >= 0 && _alg <=7) {        
            __ALGORITHM = _alg;
        } else {
            std::cout << FAILED "Convex Hull Algorithm is Invalid" ENDL;
        }
        //-- Check if Selected Space is Correct
        if (_spc >= 8 && _spc <= 9) {
            __SPACE = _spc;
        } else {
            std::cout << FAILED "Mathematical Space is Invalid" ENDL;
        }
    }
    //-- Points Constructor
    Point::Point() {
        y = GDW_HEIGHT / 2;
        x = GDW_WIDTH / 2;
        theta = 0;
    }
# endif // __CONVEX_HULL_HPP