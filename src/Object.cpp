#include "Object.hpp"


Object::Object():
    m_dielectric_constant(1.0)
{    
}

Object::~Object()
{
    for (Surface *surface : m_surfaces)
        delete surface;
}

Surface *Object::CreateSurface()
{
    Surface *new_surface = new Surface();
    m_surfaces.push_back(new_surface);
    return new_surface;
}

void Object::SetDielectricConstant(double value)
{
    m_dielectric_constant = value;
}

const std::vector<Surface *>& Object::GetSurfaces() const 
{
    return m_surfaces;
}

double Object::GetDielectricConstant() const
{
    return m_dielectric_constant;
}

void Object::Translate(Vec3 new_position)
{
    for (Surface *surface : m_surfaces)
        surface->Translate(new_position);
}

