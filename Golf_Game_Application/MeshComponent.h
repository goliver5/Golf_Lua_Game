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

	Texture2D texture;

	MeshComponent(Texture2D tex, int mesh = 0)
	{
		
		this->usingMesh = (EntityMesh)mesh;
		//std::cout << "mesh NR: " << this->usingMesh << "\n";
		//std::cout << "Loading texture: " << fileName << std::endl;
		
		//if (texture.id <= 0) std::cout << "Failed texture my check UWU nuzzle \n";

		texture = tex;
	}
};