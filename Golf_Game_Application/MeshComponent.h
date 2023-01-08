#pragma once
#include <raylib.h>
#include <iostream>

enum EntityMesh
{
	SQUARE,
	CIRCLE,
};

struct MeshComponent
{
	EntityMesh usingMesh;
	int meshNumber;
	Texture2D texture;

	MeshComponent(Texture2D tex, int meshNr = -1, int mesh = 0)
	{
		this->meshNumber = meshNr;
		this->usingMesh = (EntityMesh)mesh;

		texture = tex;
	}
};