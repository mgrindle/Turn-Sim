/*
 ============================================================================
 Name        : wind.cpp
 Author      : Mike Grindle
 Version     : v0.3.0
 Copyright   : GPLv3
 Description : Define class: Wind function definitions
 ============================================================================
 */
#include <iostream>
#include "wind.h"

//*********************************************************
// For struct type: XG_Wind_Element
//*********************************************************

void XG_Wind_Element::set_element(int wd, int ws) {      // set member values
    _wind_dir = wd;
    _wind_s = ws;
}

XG_P_Wind_Element XG_Wind_Element::get_element() const {    // get a wind element as returns a struct
    XG_P_Wind_Element pwe;
    pwe.wind_dir = _wind_dir;
    pwe.wind_s = _wind_s;
    return pwe;
}

void XG_Wind_Element::prt_wind_element() {
    std::cout << "WE: (" << _wind_dir << ", " << _wind_s << ")";
}


//****************************************
// for class type: XG_Wind
//****************************************

XG_Wind::XG_Wind() {            // constructor
    _x_bounds[0] = 0;
    _x_bounds[1] = 0;
    _y_bounds[0] = 0;
    _y_bounds[1] = 0;
    _low_elev_bound = 0;
    XG_Wind_Element _w_area_grid;
}

void XG_Wind::wind_case_a() {
    _x_bounds[0] = 9000;
    _x_bounds[1] = 11500;

    _y_bounds[0] = 11000;
    _y_bounds[1] = 13000;
    _low_elev_bound = 700;

    // leave wind element values 0 - NO WIND
}

void XG_Wind::wind_case_b() {
    _x_bounds[0] = 9000;
    _x_bounds[1] = 11500;

    _y_bounds[0] = 11000;
    _y_bounds[1] = 13000;
    _low_elev_bound = 700;

    int k = 1;          // set upper level wind elements
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            _w_area_grid[i] [j] [k].set_element(270, 7);
        }
    }

    // set lower level wind elements
    k = 0;
    int j = 0;
    _w_area_grid[0] [j] [k].set_element(180,3);
    _w_area_grid[1] [j] [k].set_element(180,3);
    _w_area_grid[2] [j] [k].set_element(180,3);
    j = 1;
    _w_area_grid[0] [j] [k].set_element(180,3);
    _w_area_grid[1] [j] [k].set_element(225,3);
    _w_area_grid[2] [j] [k].set_element(225,3);
    j = 2;
    _w_area_grid[0] [j] [k].set_element(225,3);
    _w_area_grid[1] [j] [k].set_element(225,3);
    _w_area_grid[2] [j] [k].set_element(225,3);
}

void XG_Wind::prt_wind() {
    std::cout << "*** Area Wind Display ***\n\n";
    std::cout << "                         Wind Element Coordinate Grid\n";

    for (int k = 1; k >= 0; --k) {
        if (k == 1)
            std::cout << "                              Upper Level Winds\n";
        if (k == 0)
            std::cout << "                              Lower Level Winds\n";
        std::cout << "                                     North\n";

        std::cout << "y coord. -   max\n";

        int j = 2;
        std::cout << "                   ";
        for (int i =0; i < 3; ++i) {
            _w_area_grid[i] [j] [k].prt_wind_element();
            std::cout << "  ";
        }
        std::cout << std::endl;

        std::cout << "y coord. - " << _y_bounds[1] << "\n";

        j = 1;
        std::cout << "                   ";
        for (int i =0; i < 3; ++i) {
            _w_area_grid[i] [j] [k].prt_wind_element();
            std::cout << "  ";
        }
        std::cout << std::endl;

        std::cout << "y coord. - " << _y_bounds[0] << "\n";

        j = 0;
        std::cout << "                   ";
        for (int i =0; i < 3; ++i) {
            _w_area_grid[i] [j] [k].prt_wind_element();
            std::cout << "  ";
        }
        std::cout << std::endl;

        std::cout << "y coord. -    0\n";
        //std::cout << "                 x coord. - 0, " << _x_bounds[0] << ", " << _x_bounds[1] << ", max\n";
        std::cout << "       x coord. - 0           " << _x_bounds[0] << "         " << _x_bounds[1] << "          max\n";
        std::cout << "                                     South\n\n";
    }
}
