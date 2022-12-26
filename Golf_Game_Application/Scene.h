#pragma once
#include "lua.h"
#include "entt/entt.hpp"
#include "System.h"

class Scene
{
	entt::registry registry;
	lua_State* luaState;
	std::vector<System*> systems;


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

	////Lua Functions
	//static Scene* lua_GetScene(lua_State* L);

	//static int lua_createEntity(lua_State* L);

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
inline void Scene::SetComponent(int entity, Args ...args)
{
	T& comp = registry.emplace_or_replace<T>((entt::entity)entity, args...);
}

template<typename T>
inline void Scene::RemoveComponent(int entity)
{
	registry.remove<T>((entt::entity)entity);
}
