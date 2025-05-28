#include "System.hpp"


System::~System()
{
    for (Mode *light_mode : m_light_modes)
        delete light_mode;
    
    for (Mode *mechanical_mode : m_mechanical_modes)
        delete mechanical_mode;
}

Object *System::CreateObject()
{
    Object *object = new Object();
    m_objects.push_back(object);
    return object;
}

double System::CalculateOptomechanicalCoupling_MB() const
{
    double constant = 0.0f;
    double frequency = m_light_modes[0]->GetFrequency(); // (???)
    double delta;

    for (const Mode *light_mode : m_light_modes)
    for (const Mode *mechanical_mode : m_mechanical_modes)
    for (const Object *object : m_objects)
    {
        // e - e0 = k*e0 - e0 = e0 (k - 1)
        delta = (object->GetDielectricConstant() - 1) * E0_VACUUM;

        for (const Surface &surface : object->GetSurface())
        for (const Triangle &triangle : surface.GetTriangles())
        {
            Vec3 point = triangle.CalculateMidpoint();
            
            // For linear dielectrics
            Vec3 D = object->GetDielectricConstant() * E0_VACUUM * light_mode->GetField(point);

            double electric_field_parallel = Vec3::Cross(surface.GetNormal(), light_mode->GetField(point)).Magnitude();
            double electric_displacement_perpendicular = surface.GetNormal() * D;

            constant += 
                triangle.CalculateArea() * (surface.GetNormal() * mechanical_mode->GetField(point)) *
                (delta * pow(electric_field_parallel, 2) - (1.0 / delta) * pow(electric_displacement_perpendicular, 2));
        }
    }
    
    return -(frequency / 2.0) * constant;
}

double System::CalculateOptomechanicalCoupling_PE() const
{
    return 0.0;
}

double System::CalculateNormalization() const
{
    return 1.0;
}

double System::CalculateOptomechanicalCoupling() const
{
    double coupling = 0.0;
    coupling += CalculateOptomechanicalCoupling_MB();
    coupling += CalculateOptomechanicalCoupling_PE();
    coupling /= CalculateNormalization();
    return coupling;
}

