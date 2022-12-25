#include "Scene.h"

Scene::Scene(lua_State* L)
{
	this->luaState = L;
}

Scene::~Scene()
{
}

int Scene::createEntity()
{
	return 0;
}

Scene* Scene::lua_GetScene(lua_State* L)
{
	Scene* scene = nullptr;
	if (lua_isuserdata(L, lua_upvalueindex(1)))
	{
		scene = (Scene*)lua_touserdata(L, lua_upvalueindex(1));
	}
	return scene;
}

int Scene::lua_createEntity(lua_State* L)
{
	Scene* scene = lua_GetScene(L);
	int entityID = scene->createEntity();
	return 0;
}
