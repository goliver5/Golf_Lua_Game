#pragma once
#include "System.h"

class CollisionSystem : public System
{
private:
	lua_State* L;

public:
	CollisionSystem(lua_State* L);
	~CollisionSystem();

	// Inherited via System
	virtual bool OnUpdate(entt::registry& registry, float delta) override;
};