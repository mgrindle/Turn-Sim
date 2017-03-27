#ifndef XG_GLIDER_H_INCLUDED
#define XG_GLIDER_H_INCLUDED

/*
 ============================================================================
 Name        : xg_glider.h
 Author      : Mike Grindle
 Version     : v0.0.0
 Copyright   : GPLv3
 Description : For a glider, define all constants, classes and functions.
 ============================================================================
 */
#include <cmath>
#include "xg_math.h"

// Define system wide constants

// End constant definitions


//****************************************
// for class type: XG_Vario_Press
//****************************************
class XG_Vario_Press {
private:

public:

};


//****************************************
// for class type: XG_Glider
//****************************************
class XG_Glider {
private:
    AP_Point _g_loc;                // current location
    AP_Speed_Vec _g_heading_vec;    // current heading vector (dir, as)
    int _g_curr_vert_sp;            // current vertical speed (cm/ds)
    char _g_curr_sp_mode;           // current speed mode (c,s,t)
public:

};





#endif // XG_GLIDER_H_INCLUDED
