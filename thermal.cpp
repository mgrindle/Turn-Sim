/*
 ============================================================================
 Name        : thermal.cpp
 Author      : Mike Grindle
 Version     : v0.2.0
 Copyright   : GPLv3
 Description : Define class: Thermal function definitions
 ============================================================================
 */

#include <iostream>
#include "thermal.h"

//***************************************************
// for struct type: XG_T_Profile
//***************************************************

XG_T_Profile::XG_T_Profile() {              // constructor
    // an XG_T_Profile struct has a fixed number of rows
    // based on the values of FORMATION_DURATION & THERMAL_SEG_TIMESTEPS
    int rows = FORMATION_DURATION / THERMAL_SEG_TIMESTEPS;    // total rows of profile
    height = rows;
    centers = new AP_Point[rows];           // location of segment center
}

XG_T_Profile::~XG_T_Profile() {             // destructor
    delete [] centers;
}

void XG_T_Profile::prt_t_profile(void) {    // print an entire thermal profile
    std::cout << "Thermal Profile:" << std::endl;
    int i,j;
    int col_cnt = 10 / THERMAL_SEG_TIMESTEPS;

    for (i = 0, j = 1; i < height; ++i, ++j) {
        std::cout << "Idx " << i << " - ";
        centers[i].prt_point();
        std::cout << " ";
        if (j == col_cnt) {
            std::cout << std::endl;
            j = 0;
        }
    }
}

void XG_T_Profile::prt_t_profile(XG_T_Profile &t_profile) {    // print an entire thermal profile
    std::cout << "Thermal Profile:" << std::endl;
    int i,j;
    int col_cnt = 10 / THERMAL_SEG_TIMESTEPS;

    for (i = 0, j = 1; i < height; ++i, ++j) {
        std::cout << "Idx " << i << " - ";
        centers[i].prt_point();
        std::cout << " ";
        if (j == col_cnt) {
            std::cout << std::endl;
            j = 0;
        }
    }
}

void XG_T_Profile::shift_phase_1(const int ascent_rate, const int timestep_incr, AP_Point &center) {    // @ 1st timestep, load t_profile segment 0
    centers[0] = center;
    int z_incr = ascent_rate * timestep_incr;
    centers[0].set_z(z_incr);     // z (elevation) units - centimeters
}

void XG_T_Profile::shift_phase_2(const int ascent_rate, const int timestep_incr, const int new_top_idx) {    // 2nd phase, building t_profile - no wind impact
    int z_incr = ascent_rate * timestep_incr;
    for (int i = new_top_idx; i > 0; --i) {
        centers[i] = centers[i - 1];
        centers[i].set_z(centers[i - 1].get_z() + z_incr);   // z (elevation) units - centimeters
    }
}

void XG_T_Profile::shift_phase_3(const int ascent_rate, const int timestep_incr, const int new_top_idx,
                                 const bool use_wind, const XG_Wind & ref_wind_grid) {                  // 3rd phase - incl. wind impact on top segments
    int z_incr = ascent_rate * timestep_incr;
    for (int i = new_top_idx; i > 0; --i) {
        // Calc new center position if using wind grid in simulation run.  New position
        //    based on local wind data and location of segment center at start of a cycle.
        if (use_wind) {
// TODO (ty#1#): Add to call function to move center x & y values ...
//
            // calc new x,y coord based on local wind and location
            //  of the center before it moves up and over.
//            XG_P_Wind_Element curr_wind_element = ref_wind_grid.find_local_wind(centers[i - 1]);
//            int l_wind_dir_recip = XG_P_Wind_Element.wind_dir.wind_dir_recip();
            centers[i] = centers[i - 1];
        } else {
            // not using wind, x,y coord stay the same
            centers[i] = centers[i - 1];
        }
        // new z value not dependent on wind use
        centers[i].set_z(centers[i - 1].get_z() + z_incr);   // z (elevation) units - centimeters
    }
}

//****************************************
// for class type: XG_Thermal
//****************************************

XG_Thermal::XG_Thermal(const int timestep, const int diameter,    // constructor
                        const AP_Point &base, const int ascent_rate,
                        const int disperse_elev,
                        const bool use_wind,
                        const XG_Wind &wind) : _ref_wind_grid(wind) {
    _creation_timestep = timestep;
    _diameter = diameter;           // in centimeters
    // copy AP_Point base coordinates to class member
    int coord = base.get_x();       // already in centimeters
    _base_point.set_x(coord);
    coord = base.get_y();           // already in centimeters
    _base_point.set_y(coord);
    coord = base.get_z();           // already in centimeters
    _base_point.set_z(coord);

    _col_height_idx = 0;
    _ascent_rate = TAR;             //already in cm/ds
    _disburse_elev = disperse_elev * 100;   // convert to centimeters
    XG_T_Profile _t_profile;
    _use_wind = use_wind;
}

void XG_Thermal::prt_thermal(void) {      // print members of the object
    // Note: conversions from centimeters to meters, decisecons to seconds
    std::cout << "*** XG_Thermal Object Display ***" << "\n\n";
    std::cout << "Creation timestep: " << _creation_timestep << " , " <<
                "Diameter: " << _diameter / 100 << " m, " <<
                "Base Location: Point (" << _base_point.AP_Point::get_x() / 100 << " m, " <<
                                            _base_point.AP_Point::get_y() / 100 << " m, " <<
                                            _base_point.AP_Point::get_z() / 100 << " m), " <<
                std::endl <<
                "Column Height Idx: " << _col_height_idx << " , " <<
                "Ascent Rate: " << _ascent_rate / 10 << " m/s, " <<
                "Disbursing Elevation: " << _disburse_elev / 100 << " m, " <<
                "Use Wind for location change: " << std::boolalpha << _use_wind <<
                std::endl << std::endl;
    //XG_T_Profile::prt_t_profile(_t_profile);
    _t_profile.XG_T_Profile::prt_t_profile();
    std::cout << std::endl;
}

void XG_Thermal::evolve(bool start_a_build, const int timestep_incr) {
    if (_col_height_idx >= (FORMATION_DURATION / THERMAL_SEG_TIMESTEPS)) {
        // handles a fully formed thermal to reflect existing wind impacts

// TODO (ty#1#): Add code for thermal development after build phase


    }
    else {
        // this branch is for building a new thermal profile
        if (_col_height_idx == 0 && start_a_build) {
            // populate first row of a new thermal profile
            _t_profile.XG_T_Profile::shift_phase_1(_ascent_rate, timestep_incr, _base_point);
            return;
        }
        if (_col_height_idx < (FORMATION_SPLIT / THERMAL_SEG_TIMESTEPS)) {
            // Build bottom section of thermal always no wind
            ++_col_height_idx;      // increase
            _t_profile.XG_T_Profile::shift_phase_2(_ascent_rate, timestep_incr, _col_height_idx);


        } else {
            // Build top section of the thermal profile after
            // the FORMATION_SPLIT time has passed.
            // Wind effects top half (if wind is being used)

            ++_col_height_idx;
            _t_profile.XG_T_Profile::shift_phase_3(_ascent_rate, timestep_incr, _col_height_idx,
                                                   _use_wind, _ref_wind_grid);


        }
        // end branch for building a new thermal profile
    }
}
