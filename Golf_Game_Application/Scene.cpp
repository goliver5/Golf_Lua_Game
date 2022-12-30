#include "Scene.h"
#include "Position.h"
#include "VelocityData.h"
#include <iostream>
#include "MoveScript.h"

Scene::Scene(lua_State* L)
{
	this->luaState = L;

	m_systems.push_back(new RightSystem(L));
	m_systems.push_back(new RenderSystem(L));
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

void Scene::StackDump(lua_State* L)
{
	printf("<<STACK DUMP START>>\n");
	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

		case LUA_TSTRING:  /* strings */
			printf("`%s'", lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			printf(lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			printf("%g", lua_tonumber(L, i));
			break;

		default:  /* other values */
			printf("%s", lua_typename(L, t));
			break;

		}
		printf("  ");  /* put a separator */
	}
	printf("\n<<END OF STACK DUMP>>\n");  /* end the listing */
}

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
		{ "StackDump", lua_StackDump },
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
	else if (type == "mesh") {
		hasComponent =
			scene->HasComponents<MeshComponent>(entity);
	}
	else if (type == "velocity") {
		hasComponent =
			scene->HasComponents<VelocityData>(entity);
	}
	else if (type == "moveScript") {
		hasComponent =
			scene->HasComponents<MoveScript>(entity);
	}
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
	else if (type == "mesh" &&
		scene->HasComponents<MeshComponent>(entity)) {
		MeshComponent& temp = scene->GetComponent<MeshComponent>(entity);
		return 1;
	}
	if (type == "velocity" && scene->HasComponents<VelocityData>(entity))
	{
		VelocityData& velData = scene->GetComponent<VelocityData>(entity);
		lua_pushvelocitydata(L, velData);
		return 1;
	}
	lua_pushnil(L);
	return 1;
}

int Scene::lua_SetComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = (int)lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);
	if (type == "createPlayer")//creates player
	{
		if (scene->HasComponents<Position>(entity))
		{
			std::cout << "LKLLKOI\n";
			scene->RemoveComponent<Position>(entity);
		}
		scene->StackDump(L);
		std::cout << "HFUIAWDHIUDBNAWUDIAWBDUIWADBU\n";
		//Position value(type.c_str(), entity, 69, 420, 1337);
		//value.posX = lua_tonumber(L, 3);



		const char* path = lua_tostring(L, 3);
		int ref = RefAndPushBehaviour(L, entity, path);
		//scene->SetComponent<Position>(entity, value);
		scene->SetComponent<Position>(entity, 100.f, 0.f);
		return 1;
	}


	else if (type == "position")
	{

		if (scene->HasComponents<Position>(entity))
		{
			scene->RemoveComponent<Position>(entity);
			//scene->StackDump(L);
			scene->SetComponent<Position>(entity, lua_position(L, 3));
		}
		else
		{
			scene->SetComponent<Position>(entity, 400.f, 300.f);
		}
		//Position value = lua_position(L, "golfball.lua", 3);// (type.c_str(), entity, 69, 420, 1337);
		//value.posX = lua_tonumber(L, 3);
		
		
		return 1;
	}

	else if (type == "mesh")
	{
		if (scene->HasComponents<MeshComponent>(entity))
		{
			scene->RemoveComponent<MeshComponent>(entity);
		}
		std::cout << "LIGAM\n";
		scene->SetComponent<MeshComponent>(entity, 0);
		return 1;
	}
	else if (type == "velocity")
	{

		if (scene->HasComponents<VelocityData>(entity))
		{
			scene->RemoveComponent<VelocityData>(entity);
			scene->SetComponent<VelocityData>(entity, lua_getvelocitydata(L, 3));

		}
		else
		{
			scene->SetComponent<VelocityData>(entity, 10.f, 10.f);
		}

		return 1;
	}
	else if (type == "moveScript")
	{
		if (scene->HasComponents<MoveScript>(entity))
		{
			scene->RemoveComponent<MoveScript>(entity);
		}
		//const char* path = lua_tostring(L, 3);
		int luaRef = RefAndPushBehaviour(L, entity, "golfball.lua");
		scene->SetComponent<MoveScript>(entity, "golfball.lua", luaRef, entity);

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
	else if (type == "mesh")
		scene->RemoveComponent<MeshComponent>(entity);
	else if (type == "velocity")
		scene->RemoveComponent<VelocityData>(entity);
	else if (type == "moveScript")
		scene->RemoveComponent<MoveScript>(entity);
	return 0;
}

int Scene::lua_StackDump(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	scene->StackDump(L);
	return 0;
}

int Scene::RefAndPushBehaviour(lua_State* L, int entity, const char* path)
{
	if (luaL_dofile(L, path)) std::cout << "ERROR REF AND PUSH\n";
	
	lua_pushvalue(L, -1);
	int luaTableRef = luaL_ref(L, LUA_REGISTRYINDEX);

	return luaTableRef;
}