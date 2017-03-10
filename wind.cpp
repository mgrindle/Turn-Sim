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
// For struct type: XG_P_Wind_Element
//*********************************************************



//*********************************************************
// For struct type: XG_Wind_Element
//*********************************************************

XG_Wind_Element::~XG_Wind_Element() {}      // destructor

void XG_Wind_Element::set_dir_recip() {
    if (_wind_dir > 179) {                  // values 0-359
        _wind_dir_recip = _wind_dir - 180;
    } else {
        _wind_dir_recip = _wind_dir + 180;
    }
}

void XG_Wind_Element::set_element(int wd, int ws) {      // set member values
    _wind_dir = wd;
    _wind_s = ws * 10;     // convert m/s to cm/ds
    set_dir_recip();
}

XG_P_Wind_Element XG_Wind_Element::get_element() const {    // get a wind element as returns a struct
    XG_P_Wind_Element pwe;
    pwe.wind_dir = _wind_dir;
    pwe.wind_s = _wind_s;       // in cm/ds
    pwe.wind_dir_recip = _wind_dir_recip;
    return pwe;
}

int XG_Wind_Element::wind_dir_recip() const{     // calc reciprocal of _wind_dir - the force direction
    if (_wind_dir > 179) {                  // values: 0-359
        return _wind_dir - 180;
    } else {
        return _wind_dir + 180;
    }
}

void XG_Wind_Element::prt_wind_element() {
    // convert wind_s from cm/ds to m/s
    std::cout << "WE: (" << _wind_dir << ", " << _wind_s / 10  << ")";
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

XG_Wind::~XG_Wind() {}

int XG_Wind::get_x_bounds(int idx) const {
    return _x_bounds[idx];
}

int XG_Wind::get_y_bounds(int idx) const {
    return _y_bounds[idx];
}

int XG_Wind::get_low_elev_bound() const {
    return _low_elev_bound;
}

XG_P_Wind_Element XG_Wind::get_w_area_grid_element(int i, int j, int k) const {
// TODO (ty#1#): Finish function - delete unused lines
//    XG_P_Wind_Element element;
//    element.wind_dir = _w_area_grid[i][j][k]._wind_dir;
//    element.wind_s = _w_area_grid[i][j][k]._wind_s;
//    element.wind_dir_recip = _w_area_grid[i][j][k]._wind_dir_recip;
    XG_P_Wind_Element element = _w_area_grid[i][j][k].get_element();
    return element;
}


void XG_Wind::wind_case_a() {
    _x_bounds[0] = 9000 * 100;  // convert meters to centimeters
    _x_bounds[1] = 11500 * 100;

    _y_bounds[0] = 11000 * 100;
    _y_bounds[1] = 13000 * 100;
    _low_elev_bound = 700 * 100;

    // leave wind element values 0 - NO WIND
}

void XG_Wind::wind_case_b() {
    _x_bounds[0] = 9000 * 100;  // convert meters to centimeters
    _x_bounds[1] = 11500 * 100;

    _y_bounds[0] = 11000 * 100;
    _y_bounds[1] = 13000 * 100;
    _low_elev_bound = 700 * 100;

    int k = 1;          // set upper level wind elements
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            // speed in m/s, function converts to cm/ds
            _w_area_grid[i] [j] [k].set_element(270, (7));
        }
    }

    // set lower level wind elements
    k = 0;
    int j = 0;
    // speed in m/s, function converts to cm/ds
    _w_area_grid[0] [j] [k].set_element(180, 3);
    _w_area_grid[1] [j] [k].set_element(180, 3);
    _w_area_grid[2] [j] [k].set_element(180, 3);
    j = 1;
    _w_area_grid[0] [j] [k].set_element(180, 3);
    _w_area_grid[1] [j] [k].set_element(225, 3);
    _w_area_grid[2] [j] [k].set_element(225, 3);
    j = 2;
    _w_area_grid[0] [j] [k].set_element(225, 3);
    _w_area_grid[1] [j] [k].set_element(225, 3);
    _w_area_grid[2] [j] [k].set_element(225, 3);
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

        std::cout << "y coord. - " << _y_bounds[1] / 100 << "\n";

        j = 1;
        std::cout << "                   ";
        for (int i =0; i < 3; ++i) {
            _w_area_grid[i] [j] [k].prt_wind_element();
            std::cout << "  ";
        }
        std::cout << std::endl;

        std::cout << "y coord. - " << _y_bounds[0] / 100 << "\n";

        j = 0;
        std::cout << "                   ";
        for (int i =0; i < 3; ++i) {
            _w_area_grid[i] [j] [k].prt_wind_element();
            std::cout << "  ";
        }
        std::cout << std::endl;

        std::cout << "y coord. -    0\n";
        //std::cout << "                 x coord. - 0, " << _x_bounds[0] << ", " << _x_bounds[1] << ", max\n";
        std::cout << "       x coord. - 0           " << _x_bounds[0] / 100 << "         " << _x_bounds[1] / 100 << "          max\n";
        std::cout << "                                     South\n\n";
    }
}


//XG_P_Wind_Element XG_Wind::find_local_wind(const AP_Point & point_to_move) {
//
//    // only here to get good compile
//    XG_P_Wind_Element local_wind;
//    return local_wind;
//
//}
