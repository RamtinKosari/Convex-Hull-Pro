# ifndef __CONVEX_HULL_HPP
    /**
     * @file ConvexHull.hpp
     * @author Ramtin Kosari (ramtinkosari@gmail.com)
     * @brief Implementation of Convex Hull Graham Scan and Jarvis March (Gift Wrapping) Algorithms
     * @date 2023-08-07
     */
    # define __CONVEX_HULL_HPP
    //-- Check Operating System for Window Managing Operations
    # if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) || defined(macintosh) || defined(Macintosh)
        /**
         * @brief Unix Based Operating System Configuration
         */
        # define DEFAULT_OS 0
        # pragma message \
        "Unix Based Operating System Detected"
        //-- X11 Library is Used for Displaying Windows on Unix Based Operating Systems
        # include <X11/Xlib.h>
    # elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(__WIN32__) || defined(__WINDOWS__)
        /**
         * @brief DOS Based (Windows) Operating System Configuration
         */
        # define DEFAULT_OS 1
        # pragma message \
        "DOS Based (Windows) Operating System Detected"
        //-- windows.h Library is Used for Displayings Windows on DOS Based Operating Systems
        # include <windows.h>
    # else
        /**
         * @brief None-Support Operating System
         */
        # define DEFAULT_OS -1
        # error Program is Only Avalible on Unix Based Systems and Windows
    # endif // Check Operating System
    //-- Include Configuration
    # ifndef __CONFIGS_HPP
        # include "Configs.hpp"
    # endif // __CONFIGS_HPP
    //-- Include Libraries
    # include <vector>
    # include <iostream>
    # if GRAPHICAL_VIEW
        # include <opencv4/opencv2/highgui.hpp>
        # include <opencv4/opencv2/imgproc.hpp>
    # else
        # pragma message \
        "                                                                       \
         GRAPHICAL_VIEW is Turned Off ! These Options are No Longer Usable :    \
         CALC_SPEED_FAST    CALC_SPEED_NORMAL   CALC_SPEED_DETAILS              \ 
         GENERATE_FROM_CAMERA_SOURCE    GENERATE_FROM_IMAGE                     \
         You Can Turn It On in Configuration File                               \
        "
    # endif // GRAPHICAL_VIEW
    //-- Points Generating Methodes
    enum PointGenerationMethod {
        /**
         * @brief Generate Random Points
         * @note Amount of Generated Points Can be Configured in Configs.hpp File
         */
        GENERATE_RANDOM = -1,
        /**
         * @brief Generate Points from Input Points Vector
         * @note T
         */
        GENERATE_WITH_DATA = -2,
        /**
         * @brief Generate Points from File
         * @note Input File with Specefic Structure is Needed in Term of Using this Generator
         */
        GENERATE_FROM_FILE = -3,
        /**
         * @brief Generate Points from Image
         * @note Some Algorithms Like Sobel, Treshold, Edge and More will be Affected to
         * Input Image for Extracting Edge Points 
         */
        GENERATE_FROM_IMAGE = -4,
        /**
         * @brief Generates Points from Camera
         * @note Same as Generating from Image but Live and from Camera Source
         */
        GENERATE_FROM_CAMERA_SOURCE = -5
    };
    //-- Calculating Speed Options
    enum SpeedModes {
        /**
         * @brief Fastest Speed Avalible According to OS Performance
         * @note This Speed Mode Uses Multi Threading and Multi Processing and for the
         * Result It Only Calculates Convex Hull's Points
         */
        CALC_SPEED_ULTRA = -6,
        /**
         * @brief Fast Speed
         * @note This Speed Mode is Same as Ultra Speed but With Normal Graphical Visualization
         */
        CALC_SPEED_FAST = -7,
        /**
         * @brief Normal Speed
         * @note Normal Speed Shows Algorithms Step by Step as Fast Possible
         */
        CALC_SPEED_NORMAL = -8,
        /**
         * @brief Normal Speed with Details
         * @note Shows Full Details with Configured Medium Speed and Pause After Finish
         * of each Step
         */
        CALC_SPEED_DETAILS = -9
    };
    //-- Avalible Algorithms
    enum Algorithms {
        /**
         * @brief Time Complexity : O(n * log n)
         * @note The algorithm first sorts the points lexicographically and then constructs
         * the upper and lower hulls separately. It's particularly efficient for point sets
         * that lie on or near a straight line.
         */
        MONOTONE_CHAIN_ANDREW = 0,
        /**
         * @brief Time Complexity : O(n * log h), where h is the number of points on the convex hull.
         * @note This is a randomized incremental algorithm that uses divide-and-conquer
         * techniques to build a convex hull.
         */
        KIRKPATRICK_SEIDEL = 1,
        /**
         * @brief Time Complexity : O(n * log n)
         * @note The algorithm first sorts the points lexicographically and then constructs the upper 
         * and lower hulls separately. It's particularly efficient for point sets that lie on or
         * near a straight line.
         */
        MONOTONE_CHAIN = 2,
        /**
         * @brief Time Complexity : O(n * h), where h is the number of points on the convex hull.
         * @note This algorithm iteratively selects the point with the lowest polar angle from the
         * current point and adds it to the convex hull.
         */
        JARVIS_MARCH = 3,
        /**
         * @brief Time Complexity : O(n * log n)
         * @note This algorithm sorts the points by polar angle around the lowest point and then
         * constructs the convex hull incrementally by adding points based on their relative angles.
         */
        GRAHAM_SCAN = 4,
        /**
         * @brief Time Complexity : O(n^2)
         * @note This algorithm starts with the convex hull of the first two points and then adds
         * points one by one while maintaining the convexity of the hull.
         */
        INCREMENTAL = 5,
        /**
         * @brief Time Complexity : O(n * log n) on average, O(n^2) worst-case
         * @note Quickhull uses a divide-and-conquer approach to recursively find the convex hull
         * by identifying extreme points and constructing the hull around them.
         */
        QUICK_HULL = 6,
        /**
         * @brief Time Complexity : O(n * log h), where h is the number of points on the convex hull.
         * @noteChan's algorithm combines the ideas of Graham's Scan and binary search to improve
         * performance in terms of the number of comparisons made.
         */
        CHAN = 7,
    };
    //-- Avalible Spaces to Affect Convex Hull Algorithm
    enum Spaces {
        /**
         * @brief Convex Hull in 3 Dimensional Space
         */
        IN_SPACE = 8,
        /**
         * @brief Convex Hull on 2 Dimensional Space
         */
        IN_PLANE = 9
    };
    /**
     * @brief Configuration of Convex Hull
     * @note Create Object of this Structure, Assign Configuration and then Pass It as Constructor's Argument
     */
    class Configuration {
        public :
            /**
             * @brief Graphical Visualization
             * @note It is being Set According to Configuration
             */
            bool __GRAPHICAL;
            /**
             * @brief Calculating Speed
             * @note Default : CALC_SPEED_DETAILS
             */
            int __CALCULATION;
            /**
             * @brief Convex Hull's Algorithm
             * @note Default : GRAHAM_SCAN
             */
            int __ALGORITHM;
            /**
             * @brief Points Generating Method
             * @note Default : GENERATE_WITH_DATA
             */
            int __GENERATOR;
            /**
             * @brief Convex Hull Space
             * @note Default : IN_PLANE
             */
            int __SPACE;
            /**
             * @brief Constructor that Sets Convex Hull's Configuration
             * @param _clc Calculating Speed, Default : CALC_SPEED_DETAILS
             * @param _gen Points Generating Method, Default : GENERATE_WITH_DATA
             * @param _alg Convex Hull's Algorithm, Default : GRAHAM_SCAN
             * @param _spc Convex Hull Space, Default : IN_PLANE
             */
            bool set(int _clc, int _gen, int _alg, int _spc);
    };
    //-- Points Class
    class Point {
        private:
            double theta;
            int x;
            int y;
            int z;
        public:
            Point();
    };
    //-- Convex Hull Class Definition
    class ConvexHull : public Configuration {
        private:
            bool isAutomatic;
            /**
             * @brief Points Data
             */
            std::vector<Point> points;
            /**
             * @brief ConvexHull's Configuration
             */
            Configuration cnf;
        public:
            /**
             * @brief Constructor to Initialize Convex Hull Process with Specefic Configuration
             */
            ConvexHull(Configuration);
            /**
             * @brief Method to Process Convex Hull Methodes in Order
             * @note When this Methodis Called There is No Need to Call Other Methodes
             * @return true Automatic Processing
             * @return false Client's Function Calling Processing
             */
            bool automatic();
            bool GeneratePoints();
    };
# endif // __CONVEX_HULL_HPP
