#pragma once
#include <cmath>
#include <iostream>
#include <raylib.h>


struct Vec3
{
    double x, y, z;
    
    Vec3() = default;
    
    template <typename U>
    Vec3(U p_x, U p_y, U p_z):
        x(static_cast<double>(p_x)),
        y(static_cast<double>(p_y)),
        z(static_cast<double>(p_z))
    {}
    
    double Magnitude() const;
    void Print() const; 
    Vector3 ToVector3() const;

    static Vec3 Cross(const Vec3 &a, const Vec3 &b);
    static Vec3 Normalize(const Vec3 &src);
};

#include "Vec3.inl"

