#pragma once
#include <iostream>
#include "base.h"

struct MoveScript : public base
{
	char ScriptPath[64];
	int LuaTableRef;
	int entity;

	MoveScript(const char* path = nullptr, int luaRef = 0, int entity = 0)
		:LuaTableRef(luaRef), entity(entity)
	{
		memset(ScriptPath, '\0', sizeof(ScriptPath));
		strcpy_s(ScriptPath, path);
	}
};