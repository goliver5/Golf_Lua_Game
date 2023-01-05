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

	MeshComponent(int mesh = 0, std::string fileName = "tileTest.png")
	{
		this->usingMesh = (EntityMesh)mesh;
		std::cout << "mesh NR: " << this->usingMesh << "\n";
		texture = LoadTexture(fileName.c_str());
	}
};