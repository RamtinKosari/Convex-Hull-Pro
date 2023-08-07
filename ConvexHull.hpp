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
    //-- Convex Hull Class Definition
    class ConvexHull {
        private:
        public:
    };
# endif // __CONVEX_HULL_HPP
