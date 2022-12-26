#pragma once
#include "entt/entt.hpp"

class System
{
public:
	//returns true if the system shall be removed and false if the system shall stay
	virtual bool OnUpdate(entt::registry& registry, float delta) = 0;
};