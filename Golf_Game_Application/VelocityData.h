#pragma once
#include <iostream>

struct VelocityData
{
	char ScriptPath[64];
	int LuaTableRef;

	float velocityX = 0;
	float velocityY = 0;

	VelocityData(const char* path, int luaRef, float velocityX = 0, float velocityY = 0)
		:LuaTableRef(luaRef)
	{
		memset(ScriptPath, '\0', sizeof(ScriptPath));
		strcpy_s(ScriptPath, path);
	}

};

static VelocityData lua_getvelocitydata(lua_State* L, int luaTableRef)
{
	VelocityData velData("golfball.lua", luaTableRef);

	lua_getfield(L, velData.LuaTableRef, "path");
	strcpy_s(velData.ScriptPath ,lua_tostring(L, -1));
	lua_pop(L, 1);
	
	lua_getfield(L, velData.LuaTableRef, "ref");
	velData.LuaTableRef = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, velData.LuaTableRef, "velocityX");
	velData.velocityX = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, velData.LuaTableRef, "velocityY");
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
	
	lua_pushstring(L, velData.ScriptPath);
	lua_setfield(L, -2, "path");

	lua_pushnumber(L, velData.LuaTableRef);
	lua_setfield(L, -2, "ref");

}