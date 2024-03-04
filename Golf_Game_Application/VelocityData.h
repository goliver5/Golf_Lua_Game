#pragma once
#include "lua.hpp"
#include <iostream>
#include "base.h"


struct VelocityData : public base
{
	float velocityX = 0;
	float velocityY = 0;

	VelocityData(float velocityX = 0, float velocityY = 0)
		:velocityX(velocityX), velocityY(velocityY)
	{
	}

};

static VelocityData lua_getvelocitydata(lua_State* L, int i)
{
	VelocityData velData;

	lua_getfield(L, i, "velocityX");
	velData.velocityX = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, i, "velocityY");
	velData.velocityY = lua_tonumber(L, -1);
	lua_pop(L, 1);

	return velData;
}

static void lua_pushvelocitydata(lua_State* L, VelocityData& velData)
{
	lua_newtable(L);

	lua_pushnumber(L, velData.velocityX);
	lua_setfield(L, -2, "velocityX");

	lua_pushnumber(L, velData.velocityY);
	lua_setfield(L, -2, "velocityY");
}