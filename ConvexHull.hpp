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
    //-- Include Libraries
    # include <vector>
    //-- Point Generating Methodes
    enum PointGenerationMethod {
        /**
         * @brief Generate Random Points
         * @note Amount of Generated Points Can be Configured in Configs.hpp File
         */
        GENERATE_RANDOM,
        /**
         * @brief Generate Points from File
         * @note
         */
        GENERATE_FROM_FILE,
        /**
         * @brief Generate Points from Image
         * @note Some Algorithms Like Sobel, Treshold, Edge and More will be Affected to
         * Input Image for Extracting Edge Points 
         */
        GENERATE_FROM_IMAGE,
        /**
         * @brief Generates Points from Camera
         * @note Same as Generating from Image but Live and from Camera Source
         */
        GENERATE_FROM_CAMERA_SOURCE
    };
    //-- Calculating Speed Options
    enum SpeedModes {
        /**
         * @brief Fastest Speed Avalible According to OS Performance
         * @note This Speed Mode Uses Multi Threading and Multi Processing and for the
         * Result It Only Calculates Convex Hull's Points
         */
        CALC_SPEED_ULTRA,
        /**
         * @brief Fast Speed
         * @note This Speed Mode is Same as Ultra Speed but With Normal Graphical Visualization
         */
        CALC_SPEED_FAST,
        /**
         * @brief Normal Speed
         * @note Normal Speed Shows Algorithms Step by Step as Fast Possible
         */
        CALC_SPEED_NORMAL,
        /**
         * @brief Normal Speed with Details
         * @note Shows Full Details with Configured Medium Speed and Pause After Finish
         * of each Step
         */
        CALC_SPEED_DETAILS
    };
    //-- Points Class
    class Point {
        private:
            double theta;
            int x;
            int y;
        public:
            Point();
    };
    //-- Convex Hull Class Definition
    class ConvexHull {
        private:
            std::vector<Point> points;
        public:
            //-- Constructor
            ConvexHull();
            //-- Points Generator
            bool GeneratePoints();
    };
# endif // __CONVEX_HULL_HPP
