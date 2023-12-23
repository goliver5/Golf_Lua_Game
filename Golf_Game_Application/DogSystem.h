#pragma once
#include "System.h"

class DogSystem : public System
{
private:
	lua_State* L;

public:
	DogSystem(lua_State* L);
	~DogSystem();

	// Inherited via System
	virtual bool OnUpdate(entt::registry& registry, float delta) override;
};