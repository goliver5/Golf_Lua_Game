#pragma once
#include "string.h"

struct TestBehaviour
{
	char path[64];
	int luaRef;
	int tempId;
	
	TestBehaviour(const char* path, int luaRef, int temp)
		:luaRef(luaRef), tempId(temp)
	{
		memset(this->path, '\n', 64);
		strcpy_s(this->path, 64, path);
	}
};