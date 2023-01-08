#pragma once

#include "entt/entt.hpp"
#include "raylib.h"
#include "State.h"

class Input
{
private:
	entt::registry* r;
	int playerID;
	Vector2 savedPos;
	bool holding;

	int selectedEntity = -1;

public:
	Input(entt::registry* registry);
	~Input();

	CURRENTSTATE wonHole();
	void handleMouseClick();
	void playerClick();
	void checkCollision();
	void renderLine();
};