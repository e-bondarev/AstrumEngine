#pragma once

#include "factory.h"

class Component
{
public:
	virtual ~Component() = default;

	inline virtual void OnInit() {}
};