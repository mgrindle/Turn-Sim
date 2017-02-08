/*
 ============================================================================
 Name        : wind.cpp
 Author      : Mike Grindle
 Version     : v0.0.0
 Copyright   : GPLv3
 Description : Define class: Wind function definitions
 ============================================================================
 */
#include <iostream>
#include "wind.h"

//*********************************************************
// For struct type: XG_Wind_Element
//*********************************************************

//****************************************
// for class type: XG_Wind
//****************************************

void XG_Wind::wind_case_a(XG_Wind & wp) {

    _x_bounds[] = {9000, 11500};
    _y_bounds[] = {11000, 13000};
    _low_elev_bound = 700;
}
