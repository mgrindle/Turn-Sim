/*
 ============================================================================
 Name        : xg_glider.cpp
 Author      : Mike Grindle
 Version     : v0.0.0
 Copyright   : GPLv3
 Description : Define class: xg_plane function definitions.
 ============================================================================
 */
#include <iostream>
#include "xg_glider.h"
#include "xg_math.h"

//****************************************
// for class type: XG_Vario_Press
//
// Note: newest reading is at index 0 of cache
//****************************************
XG_Vario_Press::XG_Vario_Press(const AP_Point g_start_loc, const double g_curr_sink_rate,
                               const bool g_use_elev_osc, const bool g_use_noise_gen) {
    int rows = _vp_sample_rate * _vp_cache_time;
    _vp_cache_size = rows;
    _vp_last_timestep = 0;
    _vp_readings_cache = new int[rows];
    // now populate readings cache
    double elev_lost_per_reading = g_curr_sink_rate * .002;
    double g_elev = g_start_loc.get_z();                        // timestep: 0 - glider elevation (cm)
    g_elev += -1 * g_curr_sink_rate * 10 * _vp_cache_time;      // glider elevation at 10 secs before start of simulation
    //std::cout << " drop per reading: " << elev_lost_per_reading << " -10 sec elev: " << g_elev << "\n";
    for (int i = 0; i < _vp_cache_size; ++i) {
        g_elev += elev_lost_per_reading;
        _vp_readings_cache[i] = g_elev + (g_use_elev_osc ? elevation_osc(-100 + (i * .002)) : 0) +
                                (g_use_noise_gen ? (pick_a_number(-1.0, 1.0) * .0133 * g_elev) : 0);
    }

//    // Output entire cache to a file for graphing in a spreadsheet
//    for (int i = 0; i < _vp_cache_size; i++) {
//        std::cout << _vp_readings_cache[i] << "\n";
//    }
    //std::cout << _vp_readings_cache[_vp_cache_size - 1] << "\n";
}

XG_Vario_Press::~XG_Vario_Press() {
    std::cout << "Finished XG_Vario_Press destructor.\n";
}

//****************************************
// for class type: XG_Glider
//****************************************
