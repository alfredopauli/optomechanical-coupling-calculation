#pragma once

struct Vec3
{
    double x, y, z;
    
    Vec3(): 
        x(0), y(0), z(0) {}
    
    Vec3(const Vec3 &src): 
        x(src.x), y(src.y), z(src.z) {}

    template <typename U> Vec3(const U &p_x, const U &p_y, const U &p_z):
        x(static_cast<U>(p_x)), y(static_cast<U>(p_y)), z(static_cast<U>(p_z)) {}
    
    double Mag() const
    {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }
};

inline Vec3 operator+(const Vec3 &left, const Vec3 &right)
{
    return Vec3(left.x + right.x, left.y + right.y :
}

inline Vec3 operator-(const Vec3 &left, const Vec3 &right);

inline Vec3 operator*(const double &left, const Vec3 &right);
inline Vec3 operator*(const Vec3 &left, const double &right);
inline Vec3 operator*(const Vec3 &left, const Vec3 &right);

