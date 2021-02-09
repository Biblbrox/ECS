#include <memory>

#include "component.hpp"
#include "entity.hpp"

void ecs::Entity::activate()
{
    m_alive = true;
}

const std::unordered_map<size_t, std::shared_ptr<ecs::Component>>&
ecs::Entity::getComponents() const
{
    return m_components;
}

void ecs::Entity::setEcsManager(EcsManager* ecs)
{
    m_ecsManager = ecs;
}

bool ecs::Entity::isActivate() const
{
    return m_alive;
}

void ecs::Entity::kill()
{
    m_alive = false;
}
