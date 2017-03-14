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
// Obtain revised location due to wind effects
//
// Return a revised point position due to local wind effects
AP_Point revise_loc_for_wind(const AP_Point & in_point, const int timestep_incr, const XG_Wind & wind);


#endif // XG_MATH_H_INCLUDED