#pragma once
#include "Surface.hpp"


class Object
{
    public:
        Object();
        ~Object();
        
        Surface *CreateSurface();
        void SetDielectricConstant(double value);
        
        const std::vector<Surface *>& GetSurfaces() const;
        double GetDielectricConstant() const;
        
        void Translate(Vec3 new_position);
        
    private:
        std::vector<Surface *> m_surfaces;
        double m_dielectric_constant;
};

