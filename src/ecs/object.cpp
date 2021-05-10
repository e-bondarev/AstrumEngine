#include "pch.h"

#include "object.h"

Object::Object()
{
    m_Transform = AddComponent<Transform>();
}

std::shared_ptr<Transform> Object::GetTransform()
{
    return m_Transform;
}