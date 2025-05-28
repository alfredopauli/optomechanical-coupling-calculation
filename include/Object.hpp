#pragma once
#include "Surface.hpp"


class Object
{
    public:
        Object() = default;
        
        void SetDielectricConstant(double value);
        double GetDielectricConstant() const;
        Surface& CreateSurface();
        const std::vector<Surface>& GetSurface() const;
        
    private:
        std::vector<Surface> m_surfaces;
        double m_dielectric_constant = 1.0f;
};

