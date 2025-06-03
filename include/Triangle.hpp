#pragma once
#include "Vec3.hpp"


class Triangle
{
    public:
        Triangle();
        Triangle(Vec3 a, Vec3 b, Vec3 c);
        
        const Vec3 &GetPoint(short index) const;
        const Vec3 &GetTemplatePoint(short index) const;
        const Vec3 &GetPosition() const;

        double CalculateArea() const;
        Vec3 CalculateMidpoint() const;
        void Translate(Vec3 new_position);
        void Print() const;

        static void Subdivide(const Triangle &triangle, Triangle new_triangles[4]);

    private:
        Vec3 m_template_points[3];
        Vec3 m_points[3];
        Vec3 m_position;
};

