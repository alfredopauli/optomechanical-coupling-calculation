#include "Triangle.hpp"


Triangle::Triangle()
{
    m_points[0] = { 0.0, 0.0, 0.0 };
    m_points[1] = { 0.0, 0.0, 0.0 };
    m_points[2] = { 0.0, 0.0, 0.0 };
}

Triangle::Triangle(const Vec3 a, const Vec3 b, const Vec3 c)
{
    m_points[0] = a;
    m_points[1] = b;
    m_points[2] = c;
}

const Vec3 &Triangle::GetPoint(short index) const
{
    return m_points[index];
}

double Triangle::CalculateArea() const 
{
    return (Vec3::Cross(m_points[1] - m_points[0], m_points[2] - m_points[0])).Magnitude() / 2.0;
}

Vec3 Triangle::CalculateMidpoint() const
{
    return (m_points[0] + m_points[1] + m_points[2]) / 3.0;
}

void Triangle::Print() const
{
    std::cout << "[ (x: " << m_points[0].x << ", y: " << m_points[0].y << ", z: " << m_points[0].z << ")," << std::endl;
    std::cout << "  (x: " << m_points[1].x << ", y: " << m_points[1].y << ", z: " << m_points[1].z << ")," << std::endl;
    std::cout << "  (x: " << m_points[2].x << ", y: " << m_points[2].y << ", z: " << m_points[2].z << ") ]" << std::endl;
}

void Triangle::Subdivide(const Triangle &triangle, Triangle new_triangles[4])
{
    new_triangles[0] = Triangle(
        triangle.GetPoint(0),
        (triangle.GetPoint(0) + triangle.GetPoint(1)) / 2,
        (triangle.GetPoint(0) + triangle.GetPoint(2)) / 2
    );

    new_triangles[1] = Triangle(
        triangle.GetPoint(1),
        (triangle.GetPoint(1) + triangle.GetPoint(0)) / 2,
        (triangle.GetPoint(1) + triangle.GetPoint(2)) / 2
    );

    new_triangles[2] = Triangle(
        triangle.GetPoint(2),
        (triangle.GetPoint(2) + triangle.GetPoint(0)) / 2,
        (triangle.GetPoint(2) + triangle.GetPoint(1)) / 2
    );

    new_triangles[3] = Triangle(
        (triangle.GetPoint(0) + triangle.GetPoint(1)) / 2,
        (triangle.GetPoint(0) + triangle.GetPoint(2)) / 2,
        (triangle.GetPoint(1) + triangle.GetPoint(2)) / 2
    );
}

