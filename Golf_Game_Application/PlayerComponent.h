#pragma once
#include "base.h"

struct PlayerComponent : public base
{
	int playerID = 0;
	float r;
	float g;
	float b;
	PlayerComponent(float r = 0.f, float g = 0.0f, float b = 255.f)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};