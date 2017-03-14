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

const int TAR = 30;                 // Thermal Ascent Rate (cm/ds)- the rate that
                                    // air rises in an active thermal.
                                    // *** ALSO *** It defines how a thermal
                                    // 'grows' during the thermal formation phases
                                    // of it's creation.

const int FORMATION_DURATION = 320; // The amount of timesteps in deciseconds the
                                    // thermal formation function is active. This
                                    // parameter also helps determine how large
                                    // the thermal profile structure matrix will be.
                                    // See 'struct' definition: XG_T_Profile.

const int THERMAL_SEG_TIMESTEPS = 2;// The timestep increment value that should be used
                                    // during the thermal formation phase. A new
                                    // thermal profile structure segment/row is
                                    // added/populated at each increment. This
                                    // parameter also helps determine how large
                                    // the thermal profile structure matrix will be.
                                    // See 'struct' definition: XG_T_Profile.

const int FORMATION_SPLIT = 160;    // The timestep during the thermal formation process
                                    //  which causes a split in the thermal. After
                                    // this timestep, the upper portion begins to be
                                    // effected by the low elevation winds that exist
                                    // at the thermal's center location.

const int THERMAL_DIA = 12500;      // The standard diameter (centimeters) of a thermal column.

// End constant definitions

//***************************************************
// for struct type: XG_T_Profile
//***************************************************

struct XG_T_Profile {
    AP_Point * centers;
    //int height = FORMATION_DURATION / THERMAL_SEG_TIMESTEPS;     // # of centers or rows
    int height;         // # of centers or rows

    XG_T_Profile();                 // constructor
    ~XG_T_Profile();                // destructor
    void prt_t_profile(void);       // print an entire thermal profile
    void prt_t_profile(XG_T_Profile &); // print entire profile using address of a profile
    void shift_phase_1(const int ascent_rate, const int timestep_incr, AP_Point &center);       // 1st timestep for building t_profile
    void shift_phase_2(const int ascent_rate, const int timestep_incr, const int new_top_idx);  // 2nd phase - no wind impact
    void shift_phase_3(const int ascent_rate, const int timestep_incr, const int new_top_idx,
                       const bool use_wind, const XG_Wind & ref_wind_grid);                     // 3rd phase - wind impact on top segments
};

//****************************************
// for class type: XG_Thermal
//****************************************

class XG_Thermal {
private:
    int _creation_timestep;
    int _diameter;              // in centimeters
    AP_Point _base_point;       // Point where thermal started - in centimeters
    int _col_height_idx;        // highest row (index) populated during build
    int _ascent_rate;           // in cm/ds
    int _disburse_elev;         // in centimeters
    XG_T_Profile _t_profile;
    bool _use_wind;
    const XG_Wind & _ref_wind_grid;     // pass in the class object for changing locations
public:
    XG_Thermal(const int timestep, const int diameter,    // constructor
                const AP_Point &base, const int ascent_rate,
                const int disperse_elev,
                const bool use_wind,
                const XG_Wind &wind);
    ~XG_Thermal();
    void prt_thermal(void);                                     // print all members of the object
    void evolve(bool start_a_build, const int timestep_incr);   // thermal evolution over time
};




#endif // THERMAL_H_INCLUDED
