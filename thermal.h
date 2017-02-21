#ifndef THERMAL_H_INCLUDED
#define THERMAL_H_INCLUDED

/*
 ============================================================================
 Name        : thermal.h
 Author      : Mike Grindle
 Version     : v0.2.0
 Copyright   : GPLv3
 Description : For a thermal, define all constants, classes and it's functions
 ============================================================================
 */
#include "base.h"
#include "wind.h"

// Define system wide constants

const int TAR = 3;      // Thermal Ascent Rate (m/s)- the rate that air rises in an
                        // active thermal. *** ALSO *** It defines how a thermal
                        // 'grows' during the thermal formation phases of it's
                        // creation. It is used as a step size. It is also used to
                        // calculate the size of the Profile matrix.

const int FORMATION_DURATION = 32;  // The amount of timesteps in seconds the thermal
                                    // formation function is active. This parameter
                                    // determines large the thermal profile
                                    // structure matrix will be. See 'struct'
                                    // definition: XG_T_Profile.

const int FORMATION_SPLIT = 14;     // The timestep during the thermal formation process
                                    //  which causes a split in the thermal. After
                                    // this timestep, the upper portion begins to be
                                    // effected by the low elevation winds the exist
                                    // the thermal's center location.

const int THERMAL_DIA = 12500;        // The standard diameter (centimeters) of a thermal column.

// End constant definitions

//***************************************************
// for struct type: XG_T_Profile
//***************************************************

struct XG_T_Profile {
    AP_Point * centers;
    int height = FORMATION_DURATION * TAR;     // in meters

    XG_T_Profile();                 // constructor
    ~XG_T_Profile();                // destructor
    void prt_t_profile(void);       // print an entire thermal profile
    void prt_t_profile(XG_T_Profile &); // print entire profile using address of a profile
    void shift_phase_1(const int ascent_rate, AP_Point &center);  // 1st timestep for building t_profile
    void shift_phase_2(const int ascent_rate, AP_Point &center, const int top_idx);  // 2nd phase - no wind impact
};

//****************************************
// for class type: XG_Thermal
//****************************************

class XG_Thermal {
private:
    int _creation_timestep;
    int _diameter;              // in centimeters
    AP_Point _base_point;       // in centimeters
    int _col_height_idx;        // highest row (index) populated during build
    int _ascent_rate;           // in m/s
    int _disburse_elev;         // in centimeters
    XG_T_Profile _t_profile;
    const XG_Wind & _ref_wind_grid;     // pass in the class object for changing locations
public:
// TODO (ty#1#): Add passing address to Class XG_Wind object in XG_Thermal constructor
    XG_Thermal(const int timestep, const int diameter,    // constructor
                const AP_Point &base, const int ascent_rate,
                const int disperse_elev,
                const XG_Wind &wind);
    void prt_thermal(void);             // print all members of the object
    void evolve(void);                  // thermal evolution over time
};




#endif // THERMAL_H_INCLUDED
