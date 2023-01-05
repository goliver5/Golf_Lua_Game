#pragma once

#include "entt/entt.hpp"
#include "raylib.h"

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

	void playerClick();
	void renderLine();
};