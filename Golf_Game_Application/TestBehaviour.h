#pragma once
#include "string.h"
#include "base.h"

struct TestBehaviour : public base
{
	char path[64];
	int luaRef;
	int tempId;
	
	TestBehaviour(const char* path = nullptr, int luaRef = 0, int temp = 0)
		:luaRef(luaRef), tempId(temp)
	{
		memset(this->path, '\n', 64);
		strcpy_s(this->path, path);
	}
};