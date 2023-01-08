#pragma once
#include "State.h"
#include "raylib.h"
#include "Tilemap.h"

class Editor : public State
{
private:
	Tilemap tileMap;
	lua_State* L;
	Scene scene;
	Input inputClass;

public:
	Editor(lua_State* L);
	~Editor();

	// Inherited via State
	virtual CURRENTSTATE update() override;
	virtual void render() override;

};