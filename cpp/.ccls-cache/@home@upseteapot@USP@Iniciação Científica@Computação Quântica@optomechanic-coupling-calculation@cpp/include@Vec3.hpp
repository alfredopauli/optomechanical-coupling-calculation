#pragma once
#include <cmath>
#include <iostream>

struct Vec3
{
    double x, y, z;
    
    Vec3() = default;
    
    Vec3(const Vec3 &src): 
        x(src.x), y(src.y), z(src.z) {}
    
    template <typename U> Vec3(const U &p_x, const U &p_y, const U &p_z):
        x(static_cast<U>(p_x)), y(static_cast<U>(p_y)), z(static_cast<U>(p_z)) {}
    
    double Magnitude() const;
    void Print() const; 

    static Vec3 Cross(const Vec3 &a, const Vec3 &b);
    static Vec3 Normalize(const Vec3 &src);
};

inline Vec3 operator+(const Vec3 &left, const Vec3 &right)
{
    return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
}

inline Vec3 operator-(const Vec3 &left, const Vec3 &right)
{
    return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
}

inline Vec3 operator*(const double &left, const Vec3 &right)
{
    return Vec3(left * right.x, left * right.y, left * right.z);
}

inline Vec3 operator*(const Vec3 &left, const double &right)
{
    return Vec3(left.x * right, left.y * right, left.z * right);
}

inline double operator*(const Vec3 &left, const Vec3 &right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

inline Vec3 operator/(const Vec3 &left, const double right)
{
    return Vec3(left.x / right, left.y / right, left.z / right);
}

Vec3 Vec3::Cross(const Vec3 &a, const Vec3 &b)
{
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

double Vec3::Magnitude() const
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vec3::Print() const 
{
    std::cout << "[ " << x << " " << y << " " << z << " ]" << std::endl;
}

Vec3 Vec3::Normalize(const Vec3 &src)
{
    return src / src.Magnitude();
}

