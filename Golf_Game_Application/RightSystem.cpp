#include "RightSystem.hpp"
#include "RightData.h"
#include "Position.h"
#include <iostream>

RightSystem::RightSystem(int speed)
{
    this->speed = speed;
}

bool RightSystem::OnUpdate(entt::registry& registry, float delta)
{
    
    auto view = registry.view<rightData, Position>();

    view.each([](rightData& rightdata, Position& pos)
        {
            pos.posX += rightdata.speedX;
            std::cout << pos.posX;
        }
    );

    return false;
}
