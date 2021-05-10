#pragma once

#include "component.h"

#include "math/math.h"

class Transform : public Component
{
public:
	Transform() : Component("Transform") {}

	Mat4 GetTransformationMatrix() const;

	template <typename... Args>
	void SetPosition(Args ...args) { m_Position = Vec3(std::forward<Args>(args)...); RecalculateTransformationMatrix(); }
	void SetPosition(const Vec3& position);

	template <typename... Args>
	void SetRotation(Args ...args) { m_Rotation = Vec3(std::forward<Args>(args)...); RecalculateTransformationMatrix(); }
	void SetRotation(const Vec3& rotation);

	Vec3 GetPosition() const;
	Vec3 GetRotation() const;

private:
	Mat4 m_TransformationMatrix{ Mat4(1) };
	void RecalculateTransformationMatrix();

	Vec3 m_Position{ 0, 0, 0 };
	Vec3 m_Rotation{ 0, 0, 0 };
	Vec3 m_Scale{ 1 };
};

REGISTER(Transform);