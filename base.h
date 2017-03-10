#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

/*
 ============================================================================
 Name        : base.h
 Author      : Mike Grindle
 Version     : v0.1.0
 Copyright   : GPLv3
 Description : Define all constants, classes and functions that do not
                describe the classes: plane and thermal
 ============================================================================
 */

// Define system wide constants


// End constant definitions

class AP_Point {
private:
     int _x;    // x coordinate (centimeters) (like longitude)
     int _y;    // y coordinate (centimeters) (like latitude)
     int _z;    // elevation (centimeters AGL)
public:
    // Constructor
    AP_Point(int nx = 0, int ny = 0, int nz = 0) : _x(nx * 100), _y(ny * 100), _z(nz * 100) {}
    ~AP_Point();                //destructor
    int get_x() const;          // return cm
    int get_y() const;          // return cm
    int get_z() const;          // return cm
    void set_x(const int );     // input parm in cm
    void set_y(const int );     // input parm in cm
    void set_z(const int );     // input parm in cm
    void prt_point(void) const;           // output x & y in meters, z in cm
    void prt_point(AP_Point &);     // output x & y in meters, z in cm - pass by reference
//    void prt_point(AP_Point *);     // output x & y in meters, z in cm - pass by pointer
};

//  A general speed vector defined in a polar coordinate system
//
//  Speeds setters and getters always work in cm/s units
//
class AP_Speed_Vec {
private:
    int _dir;      // direction of motion (azimuth degrees: 0-359)
    int _speed;    // speed (cm/ds)
public:
    // constructor
    AP_Speed_Vec(int ndir = 0, int nspeed = 0) : _dir(ndir), _speed(nspeed) {}
    ~AP_Speed_Vec();                    //destructor
    int get_dir() const;
    int get_speed() const;
    void set_dir(const int);
    void set_speed(const int);
    void prt_spd_vec(void);             // output speed vec
    void prt_spd_vec(AP_Speed_Vec &);   // output speed vec - pass by ref
};

#endif // BASE_H_INCLUDED
