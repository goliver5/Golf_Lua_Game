#pragma once
#include "System.h"

class RightSystem : public System
{
private:
	int speed;

public:
	RightSystem(int speed);



	// Inherited via System
	virtual bool OnUpdate(entt::registry& registry, float delta) override;

};