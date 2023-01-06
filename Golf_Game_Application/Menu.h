#pragma once
#include "State.h"
#include "raylib.h"
#include "Scene.h"
#include "Tilemap.h"

class Menu : public State
{
private:
	Vector2 ballPosition;
	const int screenWidth = 800;
	const int screenHeight = 480;
	Scene scene;

public:
	Menu(lua_State* L);
	~Menu();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};
