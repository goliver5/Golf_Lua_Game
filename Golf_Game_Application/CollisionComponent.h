#pragma once
#include "lua.hpp"
#include <iostream>

struct CollisionComponent
{
	bool x;
	bool y;
	int entity;
	int LuaTableRef;

	CollisionComponent(int entity, int luaTableRef, bool x = false, bool y = false) 
	{
		this->entity = entity;
		this->LuaTableRef = luaTableRef;
		this->x = x; 
		this->y = y; 
	}
};

static void lua_pushcollision(lua_State* L, CollisionComponent& collisionComp)
{

	lua_newtable(L);

	lua_pushboolean(L, collisionComp.x);
	lua_setfield(L, -2, "xCol");

	lua_pushboolean(L, collisionComp.y);
	lua_setfield(L, -2, "yCol");
}