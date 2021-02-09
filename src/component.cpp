#include "ecsmanager.hpp"
#include "component.hpp"

void ecs::Component::setEcsManager(EcsManager* ecs)
{
    m_ecsManager = ecs;
}

