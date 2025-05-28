#pragma once
#include <memory>
#include "Object.hpp"
#include "Emitter.hpp"

class System
{
    public:
        System() = default;
        ~System();
        
        Object &CreateObject();
        void AddLightEmitter(LightEmitter *light_emitter);
        void AddMechanicalEmitter(MechanicalEmitter *mechanical_emitter);
        double CalculateOptomechanicalCoupling() const;

    private:
        std::vector<Object> m_objects;
        std::vector<LightEmitter*> m_light_emitters;
        std::vector<MechanicalEmitter*> m_mechanical_emitters;
};

