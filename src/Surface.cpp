#include "Surface.hpp"


void Surface::CreateTriangle(Vec3 point_a, Vec3 point_b, Vec3 point_c)
{
    Triangle triangle(point_a, point_b, point_c);
    m_triangles.push_back(triangle);
    m_midpoint = (m_midpoint * (m_triangles.size() - 1) + triangle.CalculateMidpoint()) / m_triangles.size();
}

void Surface::SetNormal(Vec3 normal)
{
    m_normal = normal;
}

const std::vector<Triangle>& Surface::GetTriangles() const
{
    return m_triangles;
}

const Vec3 &Surface::GetNormal() const
{
    return m_normal;
}

const Vec3 &Surface::GetMidpoint() const
{
    return m_midpoint;
}

void Surface::CreateMesh(double threshold)
{
    m_triangles = m_RecursiveCreateMesh(m_triangles, threshold);
}

void Surface::Translate(Vec3 new_position)
{
    for (Triangle &triangle : m_triangles)
        triangle.Translate(new_position);
}

std::vector<Triangle> Surface::m_RecursiveCreateMesh(const std::vector<Triangle> &previous, double threshold)
{
    std::vector<Triangle> next_triangles;
    Triangle new_triangles[4];

    for (auto &triangle : previous)
    {
        if (triangle.CalculateArea() < threshold)
        {
            next_triangles.push_back(triangle);
            continue;
        }

        Triangle::Subdivide(triangle, new_triangles);

        next_triangles.push_back(new_triangles[0]);
        next_triangles.push_back(new_triangles[1]);
        next_triangles.push_back(new_triangles[2]);
        next_triangles.push_back(new_triangles[3]);
    }

    if (next_triangles.size() == previous.size())
        return next_triangles;

    return m_RecursiveCreateMesh(next_triangles, threshold);
}

