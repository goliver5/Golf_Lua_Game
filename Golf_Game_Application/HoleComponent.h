#pragma once

struct HoleComponent
{
	float width;
	float height;
	int state;

	HoleComponent(float width = 32.f, float height = 32.f, int state = 0)
	{
		this->width = width;
		this->height = height;
		this->state = state;
	}
};