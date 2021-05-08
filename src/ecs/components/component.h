#pragma once

#include <functional>
#include <memory>

class Component
{
public:
	virtual ~Component() = default;

	inline static std::map<std::string, std::function<void*()>> m_Factories;

	inline virtual void OnInit() {}
};

#define REGISTER(type)\
class Add##type\
{\
public:\
	Add##type()\
	{\
		A_LOG_OUT(#type " added to collection");\
		Component::m_Factories[#type] = [&] { return new type(); };\
	}\
};\
\
inline static Add##type _Add##type
