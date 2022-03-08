#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
 
class Vector3 {
public:
    Vector3() : e{ 0,0,0 } {}
    Vector3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
     
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }
 

private:
    double e[3];
};

using Point3 = Vector3;   // 3D point
using Color = Vector3;    // RGB color

#endif