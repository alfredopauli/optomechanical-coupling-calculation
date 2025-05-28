
template <typename T> T *System::CreateLightMode()
{
    static_assert(std::is_same<T,PlaneLightMode>::value, "[ERROR]: Provide a light mode type.\n");
    T *light_mode = new T();
    m_light_modes.push_back(light_mode);
    return light_mode;
}

template <typename T> T *System::CreateMechanicalMode()
{
    static_assert(std::is_same<T,PlaneMechanicalMode>::value, "[ERROR]: Provide a light mode type.\n");
    T *mechanical_mode = new T();
    m_mechanical_modes.push_back(mechanical_mode);
    return mechanical_mode;
}

