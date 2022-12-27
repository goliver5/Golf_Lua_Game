#pragma once
#include "System.h"

class RightSystem : public System
{
private:
	lua_State* L;

public:
	RightSystem(lua_State* L);



	// Inherited via System
	virtual bool OnUpdate(entt::registry& registry, float delta) override;

};