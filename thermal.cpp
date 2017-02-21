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
    // based on the values of TAR and FORMATION_DURATION
    int rows = TAR * FORMATION_DURATION;    // total rows of profile
    height = rows;
    centers = new AP_Point[rows];           // location of segment center
}

XG_T_Profile::~XG_T_Profile() {             // destructor
    delete [] centers;
}

void XG_T_Profile::prt_t_profile(void) {    // print an entire thermal profile
    std::cout << "Thermal Profile:" << std::endl;
    int i,j;
    for (i = 0, j = 1; i < height; ++i, ++j) {
        std::cout << "Idx " << i << " - ";
        centers[i].prt_point();
        std::cout << " ";
        if (j == 3) {
            std::cout << std::endl;
            j = 0;
        }
    }
}

void XG_T_Profile::prt_t_profile(XG_T_Profile &t_profile) {    // print an entire thermal profile
    std::cout << "Thermal Profile:" << std::endl;
    int i,j;
    for (i = 0, j = 1; i < height; ++i, ++j) {
        std::cout << "Idx " << i << " - ";
        centers[i].prt_point();
        std::cout << " ";
        if (j == 3) {
            std::cout << std::endl;
            j = 0;
        }
    }
}

void XG_T_Profile::shift_phase_1(const int ascent_rate, AP_Point &center) {    // @ 1st timestep, start loading t_profile
    for (int i = 0; i < ascent_rate; ++i) {
        centers[i] = center;
        centers[i].set_z((i + 1) * 100);     // z (elevation) units - centimeters
    }
}

void XG_T_Profile::shift_phase_2(const int ascent_rate, AP_Point &center, const int top_idx) {    // 2nd phase, building t_profile - no wind impact
    for (int i = top_idx; i >= ascent_rate; --i) {
        centers[i] = center;
        centers[i].set_z(centers[i - ascent_rate].get_z() + (ascent_rate * 100));   // z (elevation) units - centimeters
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
    _ascent_rate = TAR;
    _disburse_elev = disperse_elev * 100;   // convert to centimeters
    XG_T_Profile _t_profile;
    _use_wind = use_wind;
}

void XG_Thermal::prt_thermal(void) {      // print members of the object
    // Note: conversions from centimeters to meters
    std::cout << "*** XG_Thermal Object Display ***" << "\n\n";
    std::cout << "Creation timestep: " << _creation_timestep << " , " <<
                "Diameter: " << _diameter / 100 << " , " <<
                "Base Location: Point (" << _base_point.AP_Point::get_x() / 100 << ", " <<
                                            _base_point.AP_Point::get_y() / 100 << ", " <<
                                            _base_point.AP_Point::get_z() / 100 << "), " <<
                std::endl <<
                "Column Height Idx: " << _col_height_idx << " , " <<
                "Ascent Rate: " << _ascent_rate << " , " <<
                "Disbursing Elevation: " << _disburse_elev / 100 << ", " <<
                "Use Wind for location change: " << std::boolalpha << _use_wind <<
                std::endl << std::endl;
    //XG_T_Profile::prt_t_profile(_t_profile);
    _t_profile.XG_T_Profile::prt_t_profile();
    std::cout << std::endl;
}

void XG_Thermal::evolve(void) {
    if (_col_height_idx >= (_ascent_rate * FORMATION_DURATION)) {
        // handles a fully formed thermal to reflect existing wind impacts

    }
    else {
        // this branch is for building a new thermal profile
        if (_col_height_idx == 0) {
            // first timestep in thermal evolution
            _t_profile.XG_T_Profile::shift_phase_1(_ascent_rate, _base_point);
            _col_height_idx = _ascent_rate - 1;

        } else {
            // After the 'else', this code handles
            // after the first timestep in thermal evolution process
            // For the initial model - continue during timesteps 2-15
            if (_col_height_idx < (_ascent_rate * FORMATION_SPLIT)) {

                // after the first timestep in thermal evolution until
                // the FORMATION_SPLIT time.
                // For the initial model - continue during timesteps 2-15,
                // there is no wind impact during this phase
                int top_idx = _col_height_idx + _ascent_rate;
                _t_profile.XG_T_Profile::shift_phase_2(_ascent_rate, _base_point, top_idx);
                _t_profile.XG_T_Profile::shift_phase_1(_ascent_rate, _base_point);
                _col_height_idx += _ascent_rate;

            }
            else {
                // handles final creation phase of the thermal profile after
                // the FORMATION_SPLIT time has passed.
                // For the initial model, during timesteps 15-32. Wind effects top half

            }
        }
        // end branch for building a new thermal profile
    }
}
