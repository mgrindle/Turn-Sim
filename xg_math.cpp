/*
 ============================================================================
 Name        :
 Author      : Mike Grindle
 Version     : v0.0.0
 Copyright   : GPLv3
 Description : For the Turn Simulator define math functions.
 ============================================================================
 */
#include <iostream>
#include <cmath>
#include "base.h"
#include "wind.h"
#include "thermal.h"
#include "xg_math.h"

//
// Obtain the Wind Conditions for a point in space
//
//  Return a wind element for the point in space
XG_P_Wind_Element find_local_wind(const AP_Point & wind_point, const XG_Wind & wind) {
    int x_coord = wind_point.get_x();
    int y_coord = wind_point.get_y();
    int z_coord = wind_point.get_z();
    int x_idx, y_idx, z_idx;
    if (x_coord < wind.get_x_bounds(0)) {
        x_idx = 0;
    } else {
        if (x_coord < wind.get_x_bounds(1)) {
            x_idx = 1;
        } else {
            x_idx = 2;
        }
    }
    if (y_coord < wind.get_y_bounds(0)) {
        y_idx = 0;
    } else {
        if (y_coord < wind.get_y_bounds(1)) {
            y_idx = 1;
        } else {
            y_idx = 2;
        }
    }

    if (z_coord < wind.get_low_elev_bound()) {
        z_idx = 0;
    } else {
        z_idx = 1;
    }
//    // testing - print data
//    std::cout << "Wind Grid Idx - x y z: " << x_idx << " " << y_idx << " " << z_idx << " \n";

    return wind.get_w_area_grid_element(x_idx, y_idx, z_idx);
}

//
// Calc the impact of a speed vector on a point locations x,y coords only
//  Coordinate z is copied from in_point
//
// Return a revised location
AP_Point calc_new_xy(const AP_Point & in_point, const int timestep_incr, AP_Speed_Vec & speed_vec) {
    // calc the x,y offsets
    int delta_x = speed_vec.get_speed() * timestep_incr *
                    cos((90 - speed_vec.get_dir()) * pi() / 180);
    int delta_y = speed_vec.get_speed() * timestep_incr *
                    sin((90 - speed_vec.get_dir()) * pi() / 180);
    AP_Point new_loc;
    new_loc.set_x(in_point.get_x() + delta_x);
    new_loc.set_y(in_point.get_y() + delta_y);
    new_loc.set_z(in_point.get_z());

//// testing - print data
//    std::cout << "Delta x: " << delta_x << " and Delta y: " << delta_y << " New location: ";
//    new_loc.prt_point_real();
//    std::cout << "\n";
    return new_loc;
}

//
// Obtain revised plane x,y location due to wind effects
//
// Return a revised point position due to local wind effects
AP_Point revise_plane_loc_for_wind(const AP_Point & in_point, const int timestep_incr, const XG_Wind & wind,
                                   const AP_Speed_Vec & p_heading_vec) {
    // obtain local wind condition
    XG_P_Wind_Element curr_wind_element = find_local_wind(in_point, wind);
    // This section combines the two speed vectors (plane & wind)
    //
    // The result angle and speed determine the ground course the
    //      plane follows during this timestep
    int x_comp_sum = p_heading_vec.get_speed() * cos(p_heading_vec.get_dir() * pi() / 180) +        // plane comp.
                    curr_wind_element.wind_s * cos(curr_wind_element.wind_dir_recip * pi() / 180);  // wind comp.
    int y_comp_sum = p_heading_vec.get_speed() * sin(p_heading_vec.get_dir() * pi() / 180) +        // plane comp.
                    curr_wind_element.wind_s * sin(curr_wind_element.wind_dir_recip * pi() / 180);  // wind comp.
    AP_Speed_Vec course_corr_vec;
    int angle_result_i = round(atan2(y_comp_sum, x_comp_sum) * 180 / pi());
    // Correct the preliminary angle when result is
    //   a negative angle.
    // This occurs when the result vector is in
    //   the negative x zone - quadrants 2 & 3.
    //
    //         |+y
    //  Q: II  |  Q: I
    //         |       +x
    //  ----------------
    //         |
    //  Q: III |  Q: IV
    //         |
    if (angle_result_i < 0) {
                    angle_result_i += 360;
    }
    course_corr_vec.set_dir(angle_result_i);
    course_corr_vec.set_speed(round(sqrt(x_comp_sum * x_comp_sum + y_comp_sum * y_comp_sum)));

}

//
// Obtain revised thermal Center location x,y due to wind effects
//
// Return a revised point position due to local wind effects
AP_Point revise_therm_center_for_wind(const AP_Point & in_point, const int timestep_incr, const XG_Wind & wind) {
    // obtain local wind condition
    XG_P_Wind_Element curr_wind_element = find_local_wind(in_point, wind);
    // create speed vec for the wind element
    AP_Speed_Vec wind_vec;
    wind_vec.set_dir(curr_wind_element.wind_dir_recip);
    wind_vec.set_speed(curr_wind_element.wind_s);
    AP_Point rev_loc = calc_new_xy(in_point, timestep_incr, wind_vec);

//// testing - print data
//    std::cout << "\nPrint for testing.\n";
//    std::cout << "Thermal center point: ";
//    in_point.prt_point();
//    std::cout << ",  Wind Element : (" << curr_wind_element.wind_dir << ", " <<
//                curr_wind_element.wind_s << ", " << curr_wind_element.wind_dir_recip <<
//                ")\n";
//    std::cout << "Calc'd pi value: " << pi() << "\n";\
//    int delta_x = in_point.get_x() - rev_loc.get_x();
//    int delta_y = in_point.get_y() - rev_loc.get_y();
//    std::cout << "Delta values - x & y: " << delta_x << ", " << delta_y << "\n";
//    std::cout << "\nNew Thermal Center location (all in cm): ";
//    rev_loc.prt_point_real();
//    std::cout << "\nLoc revision components - old x: " << in_point.get_x() << ", delta: " << delta_x << ", new x: " << rev_loc.get_x();
//    std::cout << "\nLoc revision components - old y: " << in_point.get_y() << ", delta: " << delta_y << ", new y: " << rev_loc.get_y();
//    std::cout << "\n\nEnd program now!!\n";
//    exit (1);

    return rev_loc;
}
