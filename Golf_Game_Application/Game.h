#pragma once
#include "State.h"
#include "raylib.h"

class Game : public State
{
private:
	Vector2 ballPosition;

public:
	Game();
	~Game();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};