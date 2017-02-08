/*
 ============================================================================
 Name        : main.cpp
 Author      : Mike Grindle
 Version     : v0.2.0
 Copyright   : GPLv3
 Description : A simulation of a glider searching for thermals.

               Test various soaring methods to find and keep the glider
               circling within the rising thermal boundary. Also, waypoint
               flight path planning and altitude management strategy.
 ============================================================================
 */

#include <iostream>
#include "testing.h"
#include "base.h"
#include "wind.h"
#include "thermal.h"

using namespace std;

int main()
{

    //general_testing();

//***********************
//
//      Initialize loop variables
//
//***********************

    // time looping variables
    int current_timestep;
    int end_timestep = 40;

    // wind variables
    bool use_wind = false;

    // thermal variables
    int therm_cnt = 3;
    int begin_step = 0;
    AP_Point t_base_1(10200, 10200, 0);
    AP_Point t_base_2(10700, 10700, 0);
    AP_Point t_base_3(10500, 11700, 0);

    XG_Thermal therms[] = {
        {begin_step, THERMAL_DIA, t_base_1, TAR, 2500},
        {begin_step, THERMAL_DIA, t_base_2, TAR, 1500},
        {begin_step, THERMAL_DIA, t_base_3, TAR, 4000}
    };

    //therms[0].prt_thermal();
    //therms[1].prt_thermal();
    //therms[2].prt_thermal();

//****************************************************************************
//
//      Begin Time Loop
//
//****************************************************************************

    for (current_timestep = 0; current_timestep < end_timestep; ++current_timestep) {
        // handle each thermal's evolution for new timestep
        for (int i = 0; i < therm_cnt; ++i) {
            therms[i].evolve();
            if (current_timestep == 39)
                therms[i].prt_thermal();
        }


    }

    cout << "Hello world!" << endl;
    return 0;
}
