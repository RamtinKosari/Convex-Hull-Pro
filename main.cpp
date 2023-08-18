# include "ConvexHull.hpp"

int main() {
    //-- Create Configuration Object
    Configuration cnf;
    //-- Set Configuration
    if (cnf.set(
        CALC_SPEED_DETAILS,
        GENERATE_RANDOM,
        GRAHAM_SCAN,
        IN_PLANE
    )) {
        std::cout << TAB SUCCESS "Valid Configuration Initialized" ENDL;
    } else {
        std::cout << TAB FAILED "Can Not Initialize Configuration" ENDL;
        exit(EXIT_FAILURE);
    }
    //-- Affect Convex Hull with Initialized Configuration
    // ConvexHull convexhull
}