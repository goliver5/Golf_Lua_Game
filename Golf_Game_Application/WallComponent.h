#pragma once

struct WallComponent
{
	float width;
	float height;

	WallComponent(float width = 32.f, float height = 32.f)
	{
		this->width = width;
		this->height = height;
	}
};