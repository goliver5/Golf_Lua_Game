#pragma once

struct Position
{

	char ScriptPath[64];
	int LuaTableRef;

	int posX;
	int posY;
	int posZ;

	Position(const char* path, int luaRef, int posX, int posY, int posZ)
		:LuaTableRef(luaRef)
	{
		this->posX = posX;
		this->posY = posY;
		this->posZ = posZ;

		memset(ScriptPath, '\0', sizeof(ScriptPath));
		strcpy_s(ScriptPath, path);

	}
};