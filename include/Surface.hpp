#pragma once
#include <vector>
#include "Vec3.hpp"
#include "Triangle.hpp"


class Surface
{
    public:
        Surface() = default;
        
        void DefineNormal(Vec3 normal);
        void AddTriangle(Triangle triangle);
        
        const std::vector<Triangle>& GetTriangles() const;
        const Vec3 &GetNormal() const;
        const Vec3 &GetMidpoint() const; 

        void CreateMesh(double threshold);
       
    private:
        std::vector<Triangle> m_triangles;
        Vec3 m_normal;
        Vec3 m_midpoint;
        
        std::vector<Triangle> m_RecursiveCreateMesh(const std::vector<Triangle> &previous, double threshold);
};

