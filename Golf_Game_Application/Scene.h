#pragma once
#include "lua.hpp"
#include "entt/entt.hpp"
#include "System.h"
#include "RightSystem.hpp"

class Scene
{
	entt::registry registry;
	lua_State* luaState;
	std::vector<System*> m_systems;


public:

	Scene(lua_State* L);
	~Scene();

public:
	//C++ Functions

	//returns nr of entities
	int GetEntityCount();

	int CreateEntity();

	//checks if the entity is valid
	bool IsEntity(int entity);

	void RemoveEntity(int entity);
	
	//checks if the entity has the components
	template <typename...Args>
	bool HasComponents(int entity);

	template <typename T>
	T& GetComponent(int entity);

	template <typename T>
	void SetComponent(int entity, const T& component);

	template <typename T, typename...Args>
	void SetComponent(int entity, Args... args);

	template <typename T>
	void RemoveComponent(int entity);


	void UpdateSystems(float delta);

	//Lua Functions
public:
	static void lua_openscene(lua_State* L, Scene* scene);

private:
	static Scene* lua_GetSceneUpValue(lua_State* L);

	static int lua_GetEntityCount(lua_State* L);
	static int lua_CreateEntity(lua_State* L);
	static int lua_IsEntity(lua_State* L);
	static int lua_RemoveEntity(lua_State* L);

	static int lua_HasComponent(lua_State* L);
	static int lua_GetComponent(lua_State* L);
	static int lua_SetComponent(lua_State* L);
	static int lua_RemoveComponent(lua_State* L);

	static int RefAndPushBehaviour(lua_State* L, int entity, const char* path);
};

template<typename ...Args>
inline bool Scene::HasComponents(int entity)
{
	return registry.all_of<Args...>((entt::entity)entity);
}

template<typename T>
inline T& Scene::GetComponent(int entity)
{
	return registry.get<T>((entt::entity)entity);
}

template<typename T>
inline void Scene::SetComponent(int entity, const T& component)
{
	registry.emplace_or_replace<T>((entt::entity)entity, component);
}

template<typename T, typename ...Args>
inline void Scene::SetComponent(int entity, Args... args)
{
	T& comp = registry.emplace_or_replace<T>((entt::entity)entity, args...);
}

template<typename T>
inline void Scene::RemoveComponent(int entity)
{
	registry.remove<T>((entt::entity)entity);
}
