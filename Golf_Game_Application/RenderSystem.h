#pragma once
#include "System.h"
#include "MeshComponent.h"
#include "Input.h"

class RenderSystem : public System
{
private:
	lua_State* L;
	Input* inputClass;

public:
	RenderSystem(lua_State* L);
	void addInputClass(Input* inputClass);
	// Inherited via System
	virtual bool OnUpdate(entt::registry& registry, float delta) override;
};