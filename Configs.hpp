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
# endif // __CONFIGS_HPP