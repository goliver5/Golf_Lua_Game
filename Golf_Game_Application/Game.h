#pragma once
#include "State.h"
#include "raylib.h"
#include "Scene.h"

class Game : public State
{
private:
	lua_State* L;
	Scene scene;
	Input inputClass;
	int* strokes;

public:
	Game(lua_State* L, int* strokes);
	~Game();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};