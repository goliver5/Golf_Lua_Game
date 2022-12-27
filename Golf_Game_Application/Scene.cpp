#include "Scene.h"
#include "Position.h"
#include <iostream>

Scene::Scene(lua_State* L)
{
	this->luaState = L;

	m_systems.push_back(new RightSystem(L));
}

Scene::~Scene()
{
}

int Scene::GetEntityCount()
{
	return registry.alive();
}

int Scene::CreateEntity()
{
	return (int)registry.create();
}

bool Scene::IsEntity(int entity)
{
	return registry.valid((entt::entity)entity);
}

void Scene::RemoveEntity(int entity)
{
	registry.destroy((entt::entity)entity);
}

//Scene* Scene::lua_GetScene(lua_State* L)
//{
//	Scene* scene = nullptr;
//	if (lua_isuserdata(L, lua_upvalueindex(1)))
//	{
//		scene = (Scene*)lua_touserdata(L, lua_upvalueindex(1));
//	}
//	return scene;
//}
//
//int Scene::lua_createEntity(lua_State* L)
//{
//	Scene* scene = lua_GetScene(L);
//	int entityID = scene->createEntity();
//	return 0;
//}

void Scene::UpdateSystems(float delta)
{
	for (auto it = m_systems.begin();
		it != m_systems.end();)
	{
		if ((*it)->OnUpdate(registry, delta))
		{
			delete (*it);
			it = m_systems.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Scene::lua_openscene(lua_State* L, Scene* scene)
{
	lua_newtable(L);
	luaL_Reg sceneMethods[] =
	{
		{ "GetEntityCount", lua_GetEntityCount },
		{ "CreateEntity", lua_CreateEntity },
		{ "IsEntity", lua_IsEntity },
		{ "RemoveEntity", lua_RemoveEntity },
		{ "HasComponent", lua_HasComponent },
		{ "GetComponent", lua_GetComponent },
		{ "SetComponent", lua_SetComponent },
		{ "RemoveComponent", lua_RemoveComponent },
		{ NULL, NULL }
	};
	lua_pushlightuserdata(L, scene);
	luaL_setfuncs(L, sceneMethods, 1);
	lua_setglobal(L, "scene");
}

Scene* Scene::lua_GetSceneUpValue(lua_State* L)
{
	Scene* scene = nullptr;
	if (lua_isuserdata(L, lua_upvalueindex(1)))
	{
		scene = (Scene*)lua_touserdata(L, lua_upvalueindex(1));
	}
	return scene;
}

int Scene::lua_GetEntityCount(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int count = scene->GetEntityCount();
	lua_pushinteger(L, count);
	return 1;
}

int Scene::lua_CreateEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = scene->CreateEntity();
	lua_pushinteger(L, entity);
	std::cout << "Created Entity: " << entity << std::endl;
	return 1;
}

int Scene::lua_IsEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	bool alive = scene->IsEntity(entity);
	lua_pushboolean(L, alive);
	return 1;
}

int Scene::lua_RemoveEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	scene->RemoveEntity(entity);
	return 0;
}

int Scene::lua_HasComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);
	bool hasComponent = false;
	if (type == "position") 
		hasComponent = scene->HasComponents<Position>(entity);
	//else if (type == "component2") {
	//	hasComponent =
	//		scene->HasComponents<component2>(entity);
	//}
	lua_pushboolean(L, hasComponent);
	return 1;
}

int Scene::lua_GetComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);
	if (type == "position" && scene->HasComponents<Position>(entity)) 
	{
		Position& position = scene->GetComponent<Position>(entity);
		lua_pushposition(L, position);
		return 1;
	}
	//else if (type == "component2" &&
	//	scene->HasComponents<component2>(entity)) {
	//	component2& temp = scene->GetComponent<component2>(entity);
	//	lua_pushtemp(L, transform);
	//	return 1;
	//}
	lua_pushnil(L);
	return 1;
}

int Scene::lua_SetComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);
	if (type == "creation")
	{
		if (scene->HasComponents<Position>(entity))
		{
			std::cout << "LKLLKOI\n";
			scene->RemoveComponent<Position>(entity);
		}
		std::cout << "HFUIAWDHIUDBNAWUDIAWBDUIWADBU\n";
		//Position value(type.c_str(), entity, 69, 420, 1337);
		//value.posX = lua_tonumber(L, 3);



		const char* path = lua_tostring(L, 3);
		int ref = RefAndPushBehaviour(L, entity, path);
		//scene->SetComponent<Position>(entity, value);
		scene->SetComponent<Position>(entity, path, ref, 69, 420, 1337);
		return 1;
	}

	else if (type == "position")
	{

		if (scene->HasComponents<Position>(entity))
		{
			scene->RemoveComponent<Position>(entity);
		}
		//Position value = lua_position(L, "golfball.lua", 3);// (type.c_str(), entity, 69, 420, 1337);
		//value.posX = lua_tonumber(L, 3);

		
		scene->SetComponent<Position>(entity, lua_position(L, "golfball.lua", 3, entity));
		return 1;
	}
	//else if (type == "component2")
	//{
	//	float temp = lua_tonumber(L, 3);
	//	scene->SetComponent<component2>(entity, temp);
	//}
	return 0;
}

int Scene::lua_RemoveComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);
	if (type == "position")
		scene->RemoveComponent<Position>(entity);
	//else if (type == "component2")
	//	scene->RemoveComponent<component2>(entity);
	return 0;
}

int Scene::RefAndPushBehaviour(lua_State* L, int entity, const char* path)
{
	std::cout << path << "\n";
	luaL_dofile(L, path);
	
	lua_pushvalue(L, -1);
	int luaTableRef = luaL_ref(L, LUA_REGISTRYINDEX);

	lua_pushinteger(L, entity);
	lua_setfield(L, -2, "ID");

	lua_pushstring(L, path);
	lua_setfield(L, -2, "path");

	lua_getfield(L, -1, "OnCreate");
	lua_pushvalue(L, -2);
	lua_pcall(L, 1, 0, 0);

	return luaTableRef;
}