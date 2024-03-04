#pragma once
#include <raylib.h>
#include <iostream>
#include "base.h"

enum EntityMesh
{
	SQUARE,
	CIRCLE,
};

struct MeshComponent : public base
{
	EntityMesh usingMesh;
	int meshNumber;
	Texture2D texture;

	MeshComponent(Texture2D tex = Texture2D(), int meshNr = -1, int mesh = 0)
	{
		this->meshNumber = meshNr;
		this->usingMesh = (EntityMesh)mesh;

		texture = tex;
	}
};