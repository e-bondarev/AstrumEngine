#include "pch.h"

#include "object.h"

inline static unsigned int idAcc{ 1 };

Object::Object()
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