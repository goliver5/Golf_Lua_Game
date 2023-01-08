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
public:
	Game(lua_State* L);
	~Game();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};