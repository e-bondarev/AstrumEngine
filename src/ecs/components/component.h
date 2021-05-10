#pragma once

#include "factory.h"

class Component
{
public:
	Component(const std::string& name);

	virtual ~Component() = default;

	inline virtual void OnInit() {}

private:
	std::string m_Name;
};