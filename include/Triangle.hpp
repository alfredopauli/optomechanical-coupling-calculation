#pragma once
#include "Vec3.hpp"


class Triangle
{
    public:
        Triangle();
        Triangle(Vec3 a, Vec3 b, Vec3 c);
        
        const Vec3 &GetPoint(short index) const;

        double CalculateArea() const;
        Vec3 CalculateMidpoint() const;
        void Print() const;
        
        static void Subdivide(const Triangle &triangle, Triangle new_triangles[4]);

    private:
        Vec3 m_points[3];
};

