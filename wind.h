#ifndef WIND_H_INCLUDED
#define WIND_H_INCLUDED

/*
 ============================================================================
 Name        : wind.h
 Author      : Mike Grindle
 Version     : v0.3.0
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
// 6. Both the plane and thermals are impacted by the wind
// 7. A XG_Wind object will be passed by reference as a const to other
//      class objects, eg: XG_Thermal and XG_Glider, to be used to modify
//      positions.


//****************************************
// for struct XG_P_Wind_Element
//****************************************
//      This is a public structure used
//      as a return variable
struct XG_P_Wind_Element {
public:
    int wind_dir;       // wind direction (azimuth degrees: 0-359)
    int wind_s;         // wind speed (cm/s)
};

//****************************************
// for struct type: XG_Wind_Element
//****************************************
struct XG_Wind_Element {
private:
    int _wind_dir;      // wind direction (azimuth degrees: 0-359)
    int _wind_s;        // wind speed (cm/s)

public:
    // wind_s entered as m/s then converted/stored as cm/s
    XG_Wind_Element(int nwd = 0, int nws = 0) : _wind_dir(nwd), _wind_s(nws * 100) {}
    //~XG_Wind_Element();
    void set_element(int wd, int ws);   // set member values
    XG_P_Wind_Element get_element() const;    // get a wind element as returns a struct
    int wind_dir_recip();               // calc reciprocal of _wind_dir - the force direction
    void prt_wind_element();

};


//****************************************
// for class type: XG_Wind
//****************************************
class XG_Wind {
private:
    int _x_bounds[2];       // in centimeters
    int _y_bounds[2];       // in centimeters
    int _low_elev_bound;    // in centimeters
    XG_Wind_Element _w_area_grid[3] [3] [2];

public:
    XG_Wind();
    //~XG_Wind();
    void wind_case_a();    // For NO WINDs, initialize XG_Wind values
    void wind_case_b();    // For light winds, initialize XG_Wind values
    void prt_wind();
};

#endif // WIND_H_INCLUDED
