#pragma once
#include <iostream>

struct MoveScript
{
	char ScriptPath[64];
	int LuaTableRef;
	int entity;

	MoveScript(const char* path, int luaRef, int entity = 0)
		:LuaTableRef(luaRef), entity(entity)
	{
		memset(ScriptPath, '\0', sizeof(ScriptPath));
		strcpy_s(ScriptPath, path);
	}
};