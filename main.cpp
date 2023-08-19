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
    ) == true) {
        std::cout << SUCCESS "Valid Configuration Initialized" ENDL;
    } else {
        std::cout << FAILED "Can Not Initialize Configuration" ENDL;
        exit(EXIT_FAILURE);
    }
    //-- Create Convex Hull Process with Specefic Configuration
    ConvexHull ch(cnf);
    //-- Run Convex Hull's Process Automatically
    ch.automatic();
}