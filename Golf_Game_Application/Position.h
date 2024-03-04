#pragma once
#include "lua.hpp"
#include <iostream>
#include "base.h"


struct Position : public base
{
	float posX;
	float posY;

	Position(float posX = 0.f, float posY = 0.f)
	{
		this->posX = posX;
		this->posY = posY;

	}
};


static void lua_pushposition(lua_State* L, Position& position)
{
	lua_newtable(L);

	lua_pushnumber(L, position.posX);
	lua_setfield(L, -2, "x");

	lua_pushnumber(L, position.posY);
	lua_setfield(L, -2, "y");
}

static Position lua_position(lua_State* L, int ref)
{
	Position pos;

	lua_getfield(L, ref, "x");
	pos.posX = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, ref, "y");
	pos.posY = lua_tonumber(L, -1);
	lua_pop(L, 1);

	return pos;
}