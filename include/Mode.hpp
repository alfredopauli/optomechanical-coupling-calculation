#pragma once
#include "Vec3.hpp"
#include "Physics.hpp"


class Mode
{
    public:
        virtual void SetFrequency(double frequency);
        virtual double GetFrequency() const;
        virtual Vec3 GetField(Vec3 point) const = 0;

    protected:
        double m_frequency;
};

class PlaneLightMode : public Mode
{
    public:
        PlaneLightMode();
        
        void SetCenter(const Vec3 &center);
        void SetPropagation(const Vec3 &propagation);
        void SetPerturbation(const Vec3 &perturbation);
        
        const Vec3 &GetCenter() const;
        const Vec3 &GetPropagation() const;
        const Vec3 &GetPerturbation() const;
        
        Vec3 GetNode(const float index) const;
        
        Vec3 GetField(Vec3 point) const override;

    private:
        Vec3 m_center;
        Vec3 m_propagation;
        Vec3 m_perturbation;
};

class PlaneMechanicalMode : public Mode
{
    public:
        PlaneMechanicalMode();
        
        void SetCenter(const Vec3 &center);
        void SetPropagation(const Vec3 &propagation);
        void SetPerturbation(const Vec3 &perturbation);
        
        const Vec3 &GetCenter() const;
        const Vec3 &GetPropagation() const;
        const Vec3 &GetPerturbation() const;
        
        Vec3 GetField(Vec3 point) const override;

    private:
        Vec3 m_center;
        Vec3 m_propagation;
        Vec3 m_perturbation;
};

