#include "Emitter.hpp"


void StandingLightEmitter::SetCenter(const Vec3 &center)
{
    m_center = center;
}

void StandingLightEmitter::SetPropagation(const Vec3 &propagation)
{
    m_propagation = Vec3::Normalize(propagation);
}

void StandingLightEmitter::SetPerturbation(const Vec3 &perturbation)
{
    m_perturbation = perturbation;
}

void StandingLightEmitter::SetFrequency(const double frequency)
{
    m_frequency = frequency;
}

const Vec3 &StandingLightEmitter::GetCenter() const
{
    return m_center;
}

const Vec3 &StandingLightEmitter::GetPropagation() const
{
    return m_propagation;
}

const Vec3 &StandingLightEmitter::GetPerturbation() const
{
    return m_perturbation;
}

Vec3 StandingLightEmitter::GetNode(const float index) const
{
    return m_center + m_propagation * (LIGHT_SPEED / (2.0 * m_frequency)) * index;
}

Vec3 StandingLightEmitter::GetElectricalField(Vec3 point) const
{
    double x = (point - m_center) * m_propagation;
    return sin(2.0 * M_PI * (m_frequency / LIGHT_SPEED) * x) * m_perturbation;
}


void StandingMechanicalEmitter::SetCenter(const Vec3 &center)
{
    m_center = center;
}

void StandingMechanicalEmitter::SetPropagation(const Vec3 &propagation)
{
    m_propagation = Vec3::Normalize(propagation);
}

void StandingMechanicalEmitter::SetPerturbation(const Vec3 &perturbation)
{
    m_perturbation = perturbation;
}

const Vec3 &StandingMechanicalEmitter::GetCenter() const
{
    return m_center;
}

const Vec3 &StandingMechanicalEmitter::GetPropagation() const
{
    return m_propagation;
}

const Vec3 &StandingMechanicalEmitter::GetPerturbation() const
{
    return m_perturbation;
}

Vec3 StandingMechanicalEmitter::GetMechanicalField(Vec3 point) const
{
    double x = (point - m_center) * m_propagation;
    return cos(2.0 * M_PI * m_frequency * x) * m_perturbation;
}

