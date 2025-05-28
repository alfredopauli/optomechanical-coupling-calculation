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
        
        double CalculateOptomechanicalCoupling_MB() const;
        double CalculateOptomechanicalCoupling_PE() const;
        double CalculateNormalization() const;
        double CalculateOptomechanicalCoupling() const;

    private:
        std::vector<Object*> m_objects;
        std::vector<PlaneLightMode*> m_light_modes;
        std::vector<PlaneMechanicalMode*> m_mechanical_modes;
        
};

#include "System.inl"

