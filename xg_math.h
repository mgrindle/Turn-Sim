#ifndef XG_MATH_H_INCLUDED
#define XG_MATH_H_INCLUDED

/*
 ============================================================================
 Name        :
 Author      : Mike Grindle
 Version     : v0.0.0
 Copyright   : GPLv3
 Description : For the Turn Simulator define math function prototypes
 ============================================================================
 */
#include <cmath>
#include <random>
#include "base.h"
#include "wind.h"
#include "thermal.h"

//
// Define system wide constants
//

//const double PI = 3.14159265;
constexpr double pi() { return atan2(0, -1); }

// End constants definitions

//
// Obtain the Wind Conditions for a point in space
//
//  Return a wind element for the point in space
XG_P_Wind_Element find_local_wind(const AP_Point & wind_point, const XG_Wind & wind);

//
// Calc the impact of a speed vector on a point locations x,y coords only
//
// Return a revised location
AP_Point calc_new_xy(const AP_Point & in_point, const int timestep_incr, AP_Speed_Vec & speed_vec);


//
// Obtain revised plane x,y location due to wind effects
//
// Return a revised point position due to local wind effects
AP_Point revise_plane_loc_for_wind(const AP_Point & in_point, const int timestep_incr, const XG_Wind & wind,
                                   const AP_Speed_Vec & p_heading_vec);

//
// Obtain revised thermal center location x,y  due to wind effects
//
// Return a revised point position due to local wind effects
AP_Point revise_therm_center_for_wind(const AP_Point & in_point, const int timestep_incr, const XG_Wind & wind);

//
// Modify an Elevation (of a plane) using an Oscillating function based
//  on the timestep. This to simulate a non-steady-state glide path.
double elevation_osc(double timestep_dbl);


//
// Random Number Generator Toolkit
//
//      The following group of functions provide a single random
//      number generator toolkit that can be used anywhere in the
//      application. The implementation only offers a universal
//      distribution of integer and real numbers. Others can be added
//      later as needed. All the functions are defined in-line here
//      in this header file.
//
//      The toolkit is based on an example in a document explaining
//      new C++11 features for random number generators.  The title
//      is "N3551: Random Number Generators on C++11".

std::mt19937 & global_urng();           // define engine used

void randomize();                       //randomize seed value

int pick_a_number(int from, int thru);  // get a random integer

double pick_a_number(double from, double upto);  //get a random double

//
// End - Random Number Generator Toolkit
//

#endif // XG_MATH_H_INCLUDED
