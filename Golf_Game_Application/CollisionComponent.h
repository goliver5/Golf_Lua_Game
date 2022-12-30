#pragma once
#include "lua.hpp"
#include <iostream>

struct CollisionComponent
{
	bool x;
	bool y;
	int LuaTableRef;

	CollisionComponent(bool x = false, bool y = false) { this->x = x; this->y = y; }
};

static void lua_pushcollision(lua_State* L, CollisionComponent& collisionComp)
{


	lua_pushinteger(L, 0);
	lua_setfield(L, -2, "ID");

	lua_pushstring(L, "collision.lua");
	lua_setfield(L, -2, "path");

	lua_newtable(L);

	lua_pushnumber(L, collisionComp.x);
	lua_setfield(L, -2, "xCol");

	lua_pushnumber(L, collisionComp.y);
	lua_setfield(L, -2, "yCol");

	if (luaL_dofile(L, "collision.lua")) std::cout << "ERROR: Could not execute file " << "collision.lua" << " correctly\n";
	
	lua_pushvalue(L, -1);
	collisionComp.LuaTableRef = luaL_ref(L, LUA_REGISTRYINDEX);
}