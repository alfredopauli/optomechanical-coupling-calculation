#pragma once
#include "Vec3.hpp"

class Triangle
{
    public:
        Triangle();
        Triangle(const Vec3 a, const Vec3 b, const Vec3 c);
        
        Vec3 GetPoint(short index) const;
        double GetArea() const;
        Vec3 GetMidpoint() const;
        void Print() const;
        
        static void Subdivide(Triangle triangle, Triangle new_triangles[4]);

    private:
        Vec3 m_points[3];
};

