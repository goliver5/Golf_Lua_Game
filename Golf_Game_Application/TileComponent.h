#pragma once

struct TileComponent
{
	int entityID;
	float width;
	float height;

	TileComponent(int entityID = 0, float width = 32.f, float height = 32.f) 
	{ 
		this->entityID = entityID; 
		this->width = width;
		this->height = height;
	}
};