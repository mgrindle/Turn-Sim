#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

/*
 ============================================================================
 Name        : base.h
 Author      : Mike Grindle
 Version     : v0.0.0
 Copyright   : GPLv3
 Description : Define all constants, classes and functions that do not
                describe the classes: plane and thermal
 ============================================================================
 */

// Define system wide constants


// End constant definitions

class AP_Point {
private:
     int _x;    // meters (like longitude)
     int _y;    // meters (like latitude)
     int _z;    // elevation (meters AGL)
public:
    AP_Point(int nx = 0, int ny = 0, int nz = 0) : _x(nx), _y(ny), _z(nz) {}
    int get_x() const;
    int get_y() const;
    int get_z() const;
    void set_x(const int );
    void set_y(const int );
    void set_z(const int );
    void prt_point(void);
    void prt_point(AP_Point &);     // print a point - pass by reference
//    void prt_point(AP_Point *);     // print a point - pass by pointer
};

#endif // BASE_H_INCLUDED
