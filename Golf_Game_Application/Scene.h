#pragma once
#include "lua.h"
#include "entt/entt.hpp"

class Scene
{
	entt::registry registry;
	lua_State* luaState;
	//std::vector<System*> systems;


public:

	Scene(lua_State* L);
	~Scene();


private:
	//C++ Functions
	static int createEntity();

	//Lua Functions
	static Scene* lua_GetScene(lua_State* L);

	static int lua_createEntity(lua_State* L);

};