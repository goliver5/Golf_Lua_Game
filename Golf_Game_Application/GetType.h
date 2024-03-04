#pragma once
#include "Position.h"
#include "HoleComponent.h"
#include "WallComponent.h"
#include "MoveScript.h"
#include "VelocityData.h"
#include "PlayerComponent.h"
#include "TestBehaviour.h"
#include "MeshComponent.h"

struct types
{
	static Position position;
	static TestBehaviour testBehaviour;
	static HoleComponent holeComponent;
	static MeshComponent meshComponent;
	static VelocityData velocityData;
	static MoveScript moveScript;
	static WallComponent wallComponent;
	static PlayerComponent playerComponent;
};

static base* getType(std::string type)
{
	if (type == "behaviour") {
		return &types::testBehaviour;
	}
	else if (type == "position") {
		return &types::position;
	}
	else if (type == "mesh") {
		return &types::meshComponent;
	}
	else if (type == "velocity") {
		return &types::velocityData;
	}
	else if (type == "moveScript") {
		return &types::moveScript;
	}
	else if (type == "playerComponent") {
		return &types::playerComponent;
	}
	else if (type == "wall") {
		return &types::wallComponent;
	}
	else if (type == "hole") {
		return &types::holeComponent;
	}
}