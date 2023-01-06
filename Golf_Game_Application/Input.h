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

public:
	Input(entt::registry* registry);
	~Input();

	CURRENTSTATE wonHole();
	void playerClick();
	void checkCollision();
	void renderLine();
};