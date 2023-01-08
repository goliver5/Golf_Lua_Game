#pragma once

#include "entt/entt.hpp"
#include "raylib.h"
#include "State.h"
#include "lua.hpp"

class Scene;

class Input
{
private:
	entt::registry* r;
	int playerID;
	Vector2 savedPos;
	lua_State* L;
	bool holding;
	Scene* scenePtr;

	int selectedEntity = -1;
	int strokes = 0;

public:
	Input(lua_State* L);
	~Input();

	CURRENTSTATE wonHole();
	void setRegistry(entt::registry* registry);
	void handleMouseClick();
	void playerClick();
	void checkCollision();
	void renderLine();
};