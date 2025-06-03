#pragma once
#include <memory>
#include "Object.hpp"
#include "Mode.hpp"


class System
{
    public:
        System() = default;
        ~System();
        
        Object *CreateObject();
        template <typename T> T *CreateLightMode();
        template <typename T> T *CreateMechanicalMode();
        
        void DefineBoundary(Vec3 center, double width, double height, double length);
        
        double CalculateOptomechanicalCoupling_MB() const;
        double CalculateOptomechanicalCoupling_PE() const;
        double CalculateNormalization() const;
        double CalculateOptomechanicalCoupling() const;
        
        const Vec3 &GetBoundaryCenter() const;
        double GetBoundaryWidth() const;
        double GetBoundaryHeight() const;
        double GetBoundaryLength() const;

    private:
        Vec3 m_boundary_center;
        double m_boundary_width;
        double m_boundary_height;
        double m_boundary_length;
        std::vector<Object*> m_objects;
        std::vector<PlaneLightMode*> m_light_modes;
        std::vector<PlaneMechanicalMode*> m_mechanical_modes;
};

#include "System.inl"

