#pragma once
#include "lua.hpp"
#include <iostream>

struct Position
{
	char ScriptPath[64];
	int LuaTableRef;

	int posX;
	int posY;
	int posZ;

	Position(const char* path, int luaRef, int posX = 0, int posY = 0, int posZ = 0)
		:LuaTableRef(luaRef)
	{
		this->posX = posX;
		this->posY = posY;
		this->posZ = posZ;

		memset(ScriptPath, '\0', sizeof(ScriptPath));
		strcpy_s(ScriptPath, path);

	}

	
};

static void lua_pushposition(lua_State* L, Position& position)
{
	lua_newtable(L);

	lua_pushnumber(L, position.posX);
	lua_setfield(L, -2, "x");

	lua_pushnumber(L, position.posY);
	lua_setfield(L, -2, "y");

	lua_pushnumber(L, position.posZ);
	lua_setfield(L, -2, "z");
}

static Position lua_position(lua_State* L, const char* path, int ref, int entity)
{
	Position pos(path, ref);

	lua_getfield(L, ref, "x");
	pos.posX = lua_tonumber(L, -1);
	lua_pop(L, 1);
	std::cout << "X: " << pos.posX << "\n";

	lua_getfield(L, ref, "y");
	pos.posY = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, ref, "z");
	pos.posZ = lua_tonumber(L, -1);
	lua_pop(L, 1);

	luaL_dofile(L, path);

	lua_pushvalue(L, -1);
	pos.LuaTableRef = luaL_ref(L, LUA_REGISTRYINDEX);

	lua_pushinteger(L, entity);
	lua_setfield(L, -2, "ID");

	lua_pushstring(L, path);
	lua_setfield(L, -2, "path");

	return pos;
}