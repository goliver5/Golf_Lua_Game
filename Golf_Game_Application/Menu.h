#pragma once
#include "State.h"
#include "raylib.h"

class Menu : public State
{
private:
	Vector2 ballPosition;
	const int screenWidth = 800;
	const int screenHeight = 450;


public:
	Menu();
	~Menu();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};
