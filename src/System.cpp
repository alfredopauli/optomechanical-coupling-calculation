#include "System.hpp"

System::~System()
{
    for (LightEmitter *light_emitter : m_light_emitters)
        delete light_emitter;
    
    for (MechanicalEmitter *mechanical_emitter : m_mechanical_emitters)
        delete mechanical_emitter;
}

Object &System::CreateObject()
{
    m_objects.push_back(Object());
    return m_objects[m_objects.size() - 1];
}

void System::AddLightEmitter(LightEmitter *light_emitter)
{
    m_light_emitters.push_back(light_emitter);
}

void System::AddMechanicalEmitter(MechanicalEmitter *mechanical_emitter)
{
    m_mechanical_emitters.push_back(mechanical_emitter);
}

double System::CalculateOptomechanicalCoupling() const
{
    double constant = 0.0f;
    double delta = 1;
    double e0 = 1;

    for (const LightEmitter *light_emitter : m_light_emitters)
    for (const MechanicalEmitter *mechanical_emitter : m_mechanical_emitters)
    for (const Object &object : m_objects)
    for (const Surface &surface : object.GetSurface())
    for (const Triangle &triangle : surface.GetTriangles())
    {
        Vec3 point = triangle.GetMidpoint();

        Vec3 D = object.GetDielectricConstant() * e0 * light_emitter->GetElectricalField(point);
        double electric_field_parallel = Vec3::Cross(surface.GetNormal(), light_emitter->GetElectricalField(point)).Magnitude();
        double electric_displacement_perpendicular = surface.GetNormal() * D;

        constant +=
            (triangle.GetArea() * surface.GetNormal()) *
            (mechanical_emitter->GetMechanicalField(point)) *
            (delta * pow(electric_field_parallel, 2)
             - pow(delta, -1) * pow(electric_displacement_perpendicular, 2));
    }
    
    return constant;
}


