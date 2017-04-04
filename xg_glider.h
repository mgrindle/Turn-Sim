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
#include <string>
#include "xg_math.h"


// Define system wide constants

// End constant definitions


//****************************************
// for class type: XG_Vario_Press
//
// Note: newest reading is at index 0 of cache
//****************************************
class XG_Vario_Press {
private:
    const int _vp_sample_rate = 5000;     // Hertz - samples per second
    const int _vp_cache_time = 10;        // how long to cache readings (sec)
    int _vp_cache_size;
    int _vp_last_timestep;          // timestep cache last updated
    int * _vp_readings_cache;       // ptr to vario readings cache

public:
    XG_Vario_Press(const AP_Point g_start_loc, const double g_curr_sink_rate,
                   const bool g_use_elev_osc, const bool g_use_noise_gen);
    ~XG_Vario_Press();

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
    int _g_curr_turn_radius;        // current turning radius
    std::string _g_curr_turn_dir;   // current turning direction (cw or ccw)
    XG_Vario_Press _g_curr_vp_cache;// current pressure vario cache of readings

    int _g_min_sink;                // minimum sink rate (cm/ds)
    int _g_min_sink_sp;             // plane speed for minimum sink (cm/ds)
    int _g_ascent_eff;              // utilization of lift efficiency (integer %)
    int _g_cruise_as;               // cruise mode - airspeed (cm/ds)
    int _g_cruise_sink;             // cruise mode - sink rate (-cm/ds)
    int _g_speed_as;                // speed mode - airspeed (cm/ds)
    int _g_speed_sink;              // speed mode - sink rate (-cm/ds)
    int _g_thermal_as;              // thermal mode - airspeed (cm/ds)
    int _g_thermal_sink;            // thermal mode - sink rate (-cm/ds)
    int _g_thermal_t_radius;        // thermal mode - tight circle radius
    int _g_thermal_n_radius;        // thermal mode - normal circle radius
    int _g_thermal_w_radius;        // thermal mode - wide circle radius
    int _g_thermal_timestep_incr;   // set timestep incr to thios value diring thermal mode (ds)
    int _g_thermal_hunt_start;      // timestep thermal hunt mode began.
public:

};





#endif // XG_GLIDER_H_INCLUDED
