#pragma once

#include "component.h"

#include "math/math.h"

class Transform : public Component
{
public:
	Mat4 GetTransformationMatrix() const;

	void SetPosition(const Vec3& position);
	Vec3 GetPosition() const;

	void SetRotation(const Vec3& rotation);
	Vec3 GetRotation() const;

private:
	Mat4 m_TransformationMatrix{ Mat4(1) };
	void RecalculateTransformationMatrix();

	Vec3 m_Position;
	Vec3 m_Rotation;
	Vec3 m_Scale;
};

REGISTER(Transform);