#pragma once

#include <functional>

class ComponentFactory
{
public:
	inline static std::map<std::string, std::function<void*()>> s_Factories;

	inline static std::function<void* ()> GetFactory(const std::string& name)
	{
		return s_Factories[name];
	}
};

#define REGISTER(type)\
class Add##type\
{\
public:\
	Add##type()\
	{\
		if (ComponentFactory::s_Factories.find(#type) == ComponentFactory::s_Factories.end())\
		{\
			A_LOG_OUT(#type " added to collection");\
			ComponentFactory::s_Factories[#type] = [&] { return new type(); };\
		}\
	}\
};\
\
inline static Add##type _Add##type