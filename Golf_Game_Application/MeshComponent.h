#pragma once

enum EntityMesh
{
	GOLFBALL,
	WALL,
	GROUND,
	HOLE
};

struct MeshComponent
{
	EntityMesh usingMesh;

	MeshComponent(int mesh) { this->usingMesh = (EntityMesh)mesh; }
};