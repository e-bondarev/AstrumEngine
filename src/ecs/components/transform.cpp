#include "transform.h"

Mat4 Transform::GetTransformationMatrix() const
{
	return m_TransformationMatrix;
}

void Transform::SetPosition(const Vec3& position)
{
	m_Position = position;
	RecalculateTransformationMatrix();
}

Vec3 Transform::GetPosition() const
{
	return m_Position;
}

void Transform::SetRotation(const Vec3& rotation)
{
	m_Rotation = rotation;
	RecalculateTransformationMatrix();
}

Vec3 Transform::GetRotation() const
{
	return m_Rotation;
}

void Transform::RecalculateTransformationMatrix()
{
	m_TransformationMatrix = Math::Translate(Mat4(1), m_Position);
	m_TransformationMatrix = Math::Rotate(m_TransformationMatrix, Math::Radians(m_Rotation.x), Vec3(1, 0, 0));
	m_TransformationMatrix = Math::Rotate(m_TransformationMatrix, Math::Radians(m_Rotation.y), Vec3(0, 1, 0));
	m_TransformationMatrix = Math::Rotate(m_TransformationMatrix, Math::Radians(m_Rotation.z), Vec3(0, 0, 1));
}
