#include "Mode.hpp"


// "Mode"
void Mode::SetFrequency(double frequency)
{
    m_frequency = frequency;
}

double Mode::GetFrequency() const
{
    return m_frequency;
}

// "PlaneLightMode"
PlaneLightMode::PlaneLightMode():
    m_center(Vec3(0, 0, 0)),
    m_propagation(Vec3(1, 0, 0)),
    m_perturbation(Vec3(0, 1, 0))
{
    m_frequency = 1.0;
}

void PlaneLightMode::SetCenter(const Vec3 &center)
{
    m_center = center;
}

void PlaneLightMode::SetPropagation(const Vec3 &propagation)
{
    m_propagation = Vec3::Normalize(propagation);
}

void PlaneLightMode::SetPerturbation(const Vec3 &perturbation)
{
    m_perturbation = perturbation;
}

const Vec3 &PlaneLightMode::GetCenter() const
{
    return m_center;
}

const Vec3 &PlaneLightMode::GetPropagation() const
{
    return m_propagation;
}

const Vec3 &PlaneLightMode::GetPerturbation() const
{
    return m_perturbation;
}

Vec3 PlaneLightMode::GetNode(const float index) const
{
    return m_center + m_propagation * (LIGHT_SPEED / (2.0 * m_frequency)) * index;
}

Vec3 PlaneLightMode::GetField(Vec3 point) const
{
    double x = (point - m_center) * m_propagation;
    return sin(2.0 * M_PI * (m_frequency / LIGHT_SPEED) * x) * m_perturbation;
}


// "PlaneMechanicalMode"
PlaneMechanicalMode::PlaneMechanicalMode():
    m_center(Vec3(0, 0, 0)),
    m_propagation(Vec3(1, 0, 0)),
    m_perturbation(Vec3(0, 1, 0))
{
    m_frequency = 1.0;
}

void PlaneMechanicalMode::SetCenter(const Vec3 &center)
{
    m_center = center;
}

void PlaneMechanicalMode::SetPropagation(const Vec3 &propagation)
{
    m_propagation = Vec3::Normalize(propagation);
}

void PlaneMechanicalMode::SetPerturbation(const Vec3 &perturbation)
{
    m_perturbation = perturbation;
}

const Vec3 &PlaneMechanicalMode::GetCenter() const
{
    return m_center;
}

const Vec3 &PlaneMechanicalMode::GetPropagation() const
{
    return m_propagation;
}

const Vec3 &PlaneMechanicalMode::GetPerturbation() const
{
    return m_perturbation;
}

Vec3 PlaneMechanicalMode::GetField(Vec3 point) const
{
    double x = (point - m_center) * m_propagation;
    return cos(2.0 * M_PI * m_frequency * x) * m_perturbation;
}

