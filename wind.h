#ifndef WIND_H_INCLUDED
#define WIND_H_INCLUDED

/*
 ============================================================================
 Name        : wind.h
 Author      : Mike Grindle
 Version     : v0.0.0
 Copyright   : GPLv3
 Description : For winds, define all constants, classes and it's functions.
                Winds are not temporally based but are constant over the
                life of a simulation.
 ============================================================================
 */
#include "base.h"

//  Define system wide instants for wind

//  End system wide constants

//************************************
// Define properties of Wind
//************************************
// 1. The 'wind direction' is the direction from which the wind originates.
// 2. Wind speeds are measured in meters/second (1 m/s ~= 2.24 mph)
// 3. The wind area grid is defined as:
//      - a 3 x 3 grid
//      - the western boundary of the wind area is x=0 (longitude)
//      - the eastern boundary of the wind area is x=largest integer value
//      - the southern boundary of the wind area is y=0 (latitude)
//      - the northern boundary of the wind area is y=largest integer value
// 4. Each cell of the wind area grid contains two values:
//      - wind direction (degrees)
//      - wind speed (m/s)
// 5. A wind area has a low elevation component and an upper
//      elevation component. Delineated by an boundary elevation. The
//      upper elevation component extends unlimited.

//****************************************
// for struct type: XG_Wind_Element
//****************************************
struct XG_Wind_Element {
private:
    int _wind_dir;      // wind direction (azimuth degrees)
    int _wind_s;        // wind speed (m/s)

public:
    XG_Wind_Element();
    ~XG_Wind_Element();

};


//****************************************
// for class type: XG_Wind
//****************************************
class XG_Wind {
private:
    int _x_bounds[2];
    int _y_bounds[2];
    int _low_elev_bound;
    int _w_area_grid[3] [3];

public:
    XG_Wind();
    ~XG_Wind();
    void wind_case_a(XG_Wind &);    // For Case A, initialize XG_Wind values
};

#endif // WIND_H_INCLUDED
