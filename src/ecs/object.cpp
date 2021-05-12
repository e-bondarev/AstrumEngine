#include "pch.h"

#include "object.h"

inline static unsigned int idAcc{ 1 };

Object::Object(std::shared_ptr<Scene> & scene) : m_Scene { scene }
{
    m_Transform = AddComponent<Transform>();

    m_ID = idAcc++;
}

std::shared_ptr<Transform> Object::GetTransform()
{
    return m_Transform;
}

unsigned int Object::GetID() const
{
    return m_ID;
}