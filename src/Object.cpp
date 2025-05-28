#include "Object.hpp"


void Object::SetDielectricConstant(double value)
{
    m_dielectric_constant = value;
}

double Object::GetDielectricConstant() const
{
    return m_dielectric_constant;
}

Surface& Object::CreateSurface()
{
    m_surfaces.push_back(Surface());
    return m_surfaces[m_surfaces.size() - 1];
}

const std::vector<Surface>& Object::GetSurface() const 
{
    return m_surfaces;
}

