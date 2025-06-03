#include "Triangle.hpp"


Triangle::Triangle()
{
    m_template_points[0] = { 0.0, 0.0, 0.0 };
    m_template_points[1] = { 0.0, 0.0, 0.0 };
    m_template_points[2] = { 0.0, 0.0, 0.0 };
    
    m_points[0] = { 0.0, 0.0, 0.0 };
    m_points[1] = { 0.0, 0.0, 0.0 };
    m_points[2] = { 0.0, 0.0, 0.0 };
}

Triangle::Triangle(const Vec3 a, const Vec3 b, const Vec3 c)
{
    m_template_points[0] = a;
    m_template_points[1] = b;
    m_template_points[2] = c;
    
    m_points[0] = a;
    m_points[1] = b;
    m_points[2] = c;
}

const Vec3 &Triangle::GetPoint(short index) const
{
    return m_points[index];
}

const Vec3 &Triangle::GetTemplatePoint(short index) const
{
    return m_template_points[index];
}

const Vec3 &Triangle::GetPosition() const
{
    return m_position;
}

double Triangle::CalculateArea() const 
{
    return (Vec3::Cross(m_points[1] - m_points[0], m_points[2] - m_points[0])).Magnitude() / 2.0;
}

Vec3 Triangle::CalculateMidpoint() const
{
    return (m_points[0] + m_points[1] + m_points[2]) / 3.0;
}

void Triangle::Translate(Vec3 new_position)
{
    m_position = new_position;
    m_points[0] = m_template_points[0] + m_position;
    m_points[1] = m_template_points[1] + m_position;
    m_points[2] = m_template_points[2] + m_position;
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
        triangle.GetTemplatePoint(0),
        (triangle.GetTemplatePoint(0) + triangle.GetTemplatePoint(1)) / 2,
        (triangle.GetTemplatePoint(0) + triangle.GetTemplatePoint(2)) / 2
    );
    new_triangles[0].Translate(triangle.GetPosition());

    new_triangles[1] = Triangle(
        triangle.GetTemplatePoint(1),
        (triangle.GetTemplatePoint(1) + triangle.GetTemplatePoint(0)) / 2,
        (triangle.GetTemplatePoint(1) + triangle.GetTemplatePoint(2)) / 2
    );
    new_triangles[1].Translate(triangle.GetPosition());

    new_triangles[2] = Triangle(
        triangle.GetTemplatePoint(2),
        (triangle.GetTemplatePoint(2) + triangle.GetTemplatePoint(0)) / 2,
        (triangle.GetTemplatePoint(2) + triangle.GetTemplatePoint(1)) / 2
    );
    new_triangles[2].Translate(triangle.GetPosition());

    new_triangles[3] = Triangle(
        (triangle.GetTemplatePoint(0) + triangle.GetTemplatePoint(1)) / 2,
        (triangle.GetTemplatePoint(0) + triangle.GetTemplatePoint(2)) / 2,
        (triangle.GetTemplatePoint(1) + triangle.GetTemplatePoint(2)) / 2
    );
    new_triangles[3].Translate(triangle.GetPosition());
}

