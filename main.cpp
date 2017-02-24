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

               Thermals are dynamic. In that, they are fixed-size (diameter
               and column height) but are constantly rising and moving location
               (based on local wind condition).

               As a methodology, I am attempting to use all integer math.

               **************************************************************************
               Units of Measure:
                    - Distances, coordinates, elevations are specified/entered in meters
                        but are converted and stored/used in centimeters.
                                              ^^^^^^^^^^^
                    - Times are specified in seconds but are converted to
                        and stored/used in deciseconds (1/10 second).
                            ^^^^^^^^^^^

                    - Timesteps are always in deciseconds (1/10 second).

                    - Plane and wind speeds are specified/entered in meters/second
                        but are converted and stored/used in centimeters/decisecond.
                                              ^^^^^^^^^^^

                                Entered     Stored/Used
                    Time:       1 sec           10 ds
                    Timestep:   1 ds            1 ds
                    Distance:   1 m             100 cm
                    Speed:      1 m/s           10 cm/ds

                **************************************************************************

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

    //general_testing1();       // AP_Point, XG_T_Profile and XG_Thermal
    //general_testing2();         // XG_Wind_Element, XG_Wind

//**************************************************
//
//      Initialize loop variables
//
//      See Notes above about Units of Measure
//
//**************************************************

    // time looping variables
    int current_timestep;
    int main_timestep_incr = THERMAL_SEG_TIMESTEPS;
    int end_timestep = 200;

    // wind variables
    bool use_wind = false;  // use wind data in the simulation
    XG_Wind wind_grid;
    wind_grid.wind_case_b();

    wind_grid.prt_wind();

    // thermal variables
    //
    // need timestep_incr = 2 for building initial thermals
    int therm_cnt = 3;      // number of thermals to create
    int begin_step = 2;
    bool begin_build = true;
    AP_Point t_base_1(10200, 10200, 0);
    AP_Point t_base_2(10700, 10700, 0);
    AP_Point t_base_3(10500, 11700, 0);

    XG_Thermal therms[] = {
        {begin_step, THERMAL_DIA, t_base_1, TAR, 2500, use_wind, wind_grid},
        {begin_step, THERMAL_DIA, t_base_2, TAR, 1500, use_wind, wind_grid},
        {begin_step, THERMAL_DIA, t_base_3, TAR, 4000, use_wind, wind_grid},
    };

    //therms[0].prt_thermal();
    //therms[1].prt_thermal();
    //therms[2].prt_thermal();

    // plane variables
    bool p_in_thermal_mode = false;     // Is the plane set in thermaling mode?

//****************************************************************************
//
//      Begin Time Loop
//
//****************************************************************************

    for (current_timestep = 2; current_timestep < end_timestep; current_timestep += main_timestep_incr) {

        if (current_timestep < FORMATION_DURATION && main_timestep_incr != THERMAL_SEG_TIMESTEPS) {
            cout << "******************************************************************\n";
            cout << "*                                                                *\n";
            cout << "*   ABORT EXECUTION - Timestep increment not = 2 during          *\n";
            cout << "*                     the creation of thermal columns.           *\n";
            cout << "*                                                                *\n";
            cout << "*                     Plane may have encountered a thermal       *\n";
            cout << "*                     before thermal creation was complete.      *\n";
            cout << "*                                                                *\n";
            cout << "******************************************************************\n";
            return 10;
        }

        // handle each thermal's evolution for new timestep
        for (int i = 0; i < therm_cnt; ++i) {
            therms[i].evolve(begin_build, main_timestep_incr);
            if (current_timestep == 160) {
                cout << "Thermal # " << i << endl;
                therms[i].prt_thermal();
            }
        }
        begin_build = false;

    }

    cout << "Hello world!" << endl;
    return 0;
}
