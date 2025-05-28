#pragma once
#include "Vec3.hpp"
#include "Physics.hpp"


class LightEmitter
{
    public:
        virtual Vec3 GetElectricalField(Vec3 point) const = 0;
};

class MechanicalEmitter
{
    public: 
        virtual Vec3 GetMechanicalField(Vec3 point) const = 0;
};

class StandingLightEmitter : public LightEmitter
{
    public:
        StandingLightEmitter():
            m_center(Vec3(0, 0, 0)),
            m_propagation(Vec3(1, 0, 0)),
            m_perturbation(Vec3(0, 1, 0)),
            m_frequency(1)
        {}
        
        void SetCenter(const Vec3 &center);
        void SetPropagation(const Vec3 &propagation);
        void SetPerturbation(const Vec3 &perturbation);
        void SetFrequency(const double frequency);
        
        const Vec3 &GetCenter() const;
        const Vec3 &GetPropagation() const;
        const Vec3 &GetPerturbation() const;
        Vec3 GetNode(const float index) const;
        
        Vec3 GetElectricalField(Vec3 point) const override;

    private:
        Vec3 m_center;
        Vec3 m_propagation;
        Vec3 m_perturbation;
        double m_frequency;
};

class StandingMechanicalEmitter : public MechanicalEmitter
{
    public:
        StandingMechanicalEmitter():
            m_center(Vec3(0, 0, 0)),
            m_propagation(Vec3(1, 0, 0)),
            m_perturbation(Vec3(0, 1, 0)),
            m_frequency(1)
        {}
        
        void SetCenter(const Vec3 &center);
        void SetPropagation(const Vec3 &propagation);
        void SetPerturbation(const Vec3 &perturbation);
        
        const Vec3 &GetCenter() const;
        const Vec3 &GetPropagation() const;
        const Vec3 &GetPerturbation() const;
        
        Vec3 GetMechanicalField(Vec3 point) const override;

    private:
        Vec3 m_center;
        Vec3 m_propagation;
        Vec3 m_perturbation;
        double m_frequency;
};

