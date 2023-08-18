# ifndef __CONFIGS_HPP
    /**
     * @file Configs.hpp
     * @author Ramtin Kosari (ramtinkosari@gmail.com)
     * @brief Configuration File that is Used by Program
     * @date 2023-08-07
     */
    # define __CONFIGS_HPP
    /**
     * @brief Graphical Visualization
     * @note If True, It will Take Some More Moments to Process Data
     * @note Also Graphical Operations Uses OpenCV That Should be Installed
     * on Your System in Order to Use This Option
     */
    # define GRAPHICAL_VIEW true
    /**
     * @brief Width of Graphical Display Window
     * @note If Higher than Screen's Width, It Will Initialized to Your 
     * Screen's Width to Prevent Displaying Outside of Screen
     */
    # define GDW_WIDTH 1000
    /**
     * @brief Height of Graphical Display Window
     * @note If Higher than Screen's Height, It Will Initialized to Your 
     * Screen's Height to Prevent Displaying Outside of Screen
     */
    # define GDW_HEIGHT 1000
    /**
     * @brief Amount of Random Points that are Going to be Generated
     */
    # define RANDOM_POINTS_AMOUNT 1000
    /**
     * @brief Enables in-Terminal Log Messages
     */
    # define LOG_MESSAGES true
    //-- in-Terminal Log Definitions
    # define WARNING "\033[38;2;255;255;0m[WARNING]\033[0m "
    # define SUCCESS "\033[38;2;0;255;0m[SUCCESS]\033[0m "
    # define FAILED "\033[38;2;255;0;0m[FAILED]\033[0m "
    # define LOG "\033[38;2;150;150;150m[LOG]\033[0m "
    # define ENDL "\n"
    # define TAB "   "
# endif // __CONFIGS_HPP