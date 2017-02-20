/*
 ============================================================================
 Name        : base.cpp
 Author      : Mike Grindle
 Version     : v0.1.0
 Copyright   : GPLv3
 Description : Define class: Base function definitions
 ============================================================================
 */

#include <iostream>
#include "base.h"

// For AP_Point class

int AP_Point::get_x() const {
    return _x;
};

int AP_Point::get_y() const {
    return _y;
};

int AP_Point::get_z() const {
    return _z;
};

void AP_Point::set_x(const int new_x) {
    _x = new_x;
};

void AP_Point::set_y(const int new_y) {
    _y = new_y;
};

void AP_Point::set_z(const int new_z) {
    _z = new_z;
};

// coordinates are output in meters
void AP_Point::prt_point(void) {
    std::cout << "AP_Point: (" << _x/100 << ", " << _y/100 << ", " << _z/100 << ")";
}

// Using pass by reference to a AP_Point, print a point
// coordinates are output in meters
void AP_Point::prt_point(AP_Point & p) {
    std::cout << "AP_Point: (" << p._x/100 << ", " << p._y/100 << ", " << p._z/100 << ")";
}

//// Using pass by pointer to a AP_Point, print a point
//// coordinates are output in meters
//void AP_Point::prt_point(AP_Point * p) {
////    std::cout << "AP_Point: (" << *p.get_x()/100 << ", " << *p._y/100 << ", " << *p._z/100 << ")";
//}


// For AP_Speed_Vec class

int AP_Speed_Vec::get_dir() const {
    return _dir;
}

int AP_Speed_Vec::get_speed() const {
    return _speed;
}

void AP_Speed_Vec::set_dir(const int new_dir) {
    _dir = new_dir;
}

void AP_Speed_Vec::set_speed(const int new_speed) {
    _speed = new_speed;       // new_speed parameter must be cm/s
}

void AP_Speed_Vec::prt_spd_vec(void) {             // output speed vec
    std::cout << "AP_Speed_Vec: (" << _dir << "deg., " << _speed << "cm/s)";
}

void AP_Speed_Vec::prt_spd_vec(AP_Speed_Vec & sv) {   // output speed vec - pass by ref
    std::cout << "AP_Speed_Vec: (" << sv._dir << "deg., " << sv._speed << "cm/s)";
}
