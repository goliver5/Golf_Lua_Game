#pragma once
#include "System.h"
#include "MeshComponent.h"

class RenderSystem : public System
{
private:
	lua_State* L;


public:
	RenderSystem(lua_State* L);

	// Inherited via System
	virtual bool OnUpdate(entt::registry& registry, float delta) override;
};