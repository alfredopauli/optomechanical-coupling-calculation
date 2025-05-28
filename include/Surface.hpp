#pragma once
#include <vector>
#include "Vec3.hpp"
#include "Triangle.hpp"


// All the triangles have the same normal, they lie on the same plane!
// I will add a condition that ensures that, but for now i need to do it manually
class Surface
{
    public:
        Surface() = default;
        
        void DefineNormal(Vec3 normal);
        Vec3 GetNormal() const;
        
        void AddTriangle(Triangle triangle);
        const std::vector<Triangle>& GetTriangles() const;
        Vec3 GetMidpoint() const; 

        void CreateMesh(double threshold);
       
    private:
        std::vector<Triangle> m_triangles;
        Vec3 m_normal;
        Vec3 m_midpoint;
        
        std::vector<Triangle> m_RecursiveCreateMesh(const std::vector<Triangle> &previous, double threshold);
};
