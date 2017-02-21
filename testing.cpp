/*
 ============================================================================
 Name        : testing.cpp
 Author      : Mike Grindle
 Version     : v0.2.0
 Copyright   : GPLv3
 Description : Testing function definitions.
 ============================================================================
 */
#include <iostream>
#include "base.h"
#include "wind.h"
#include "thermal.h"

using namespace std;

// General Testing of classes: AP_Point, XG_T_Profile and XG_Thermal
void general_testing1(void) {

    //***********************
    // class: AP_Point
    //***********************
    AP_Point p1;
    cout << "Print p1: ";
    p1.prt_point();

    AP_Point p2(10000, 10000, 0);
    cout << endl << "Print p2: ";
    p2.prt_point();

    AP_Point p3 = p2;       // copy an AP_Point to a new AP_Point object
    p3.set_x(15000);
    p3.set_y(12000);
    cout << "\nPrint p3: ";
    p3.prt_point();

    // end testing class: AP_Point

    //******************************
    // class XG_T_Profile
    //******************************
    XG_T_Profile test_prof;     // create object
    cout << "\nPrint test_prof struct:" << endl;    // print the hard way
    for (int i = 0; i < test_prof.height; ++i) {
        cout << "Idx " << i << " - ";
        test_prof.centers[i].prt_point();
        cout << endl;
    }
    cout << endl;

    test_prof.prt_t_profile();  // print using class function
    cout << endl;

    // end testing class: XG_T_Profile

    //**********************************
    // class: XG_Thermal
    //**********************************

    // need XG_Wind object for thermal class
    XG_Wind test_wind_grid;
    test_wind_grid.wind_case_b();

    // app variables needed for this class
    int timestep = 0;

    XG_Thermal therm1 = {timestep, THERMAL_DIA,
                p2, TAR,
                2500, test_wind_grid};
    therm1.prt_thermal();


    XG_Thermal therm_arr_1[] = {
        {timestep, THERMAL_DIA, p2, TAR, 2500, test_wind_grid},
        {timestep, THERMAL_DIA, p3, TAR, 1500, test_wind_grid}
    };

    therm_arr_1[1].prt_thermal();

    // end testing class: XG_Thermal

}

// General Testing of Classes: XG_Wind_Element, XG_Wind
void general_testing2(void) {
    XG_Wind wind_a;
    wind_a.prt_wind();
}
