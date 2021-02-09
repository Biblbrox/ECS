#include <memory>

#include "ecsmanager.hpp"

std::shared_ptr<ecs::Entity> ecs::EcsManager::createEntity(const std::string& name)
{
    std::shared_ptr ent = std::make_shared<Entity>();
    ent->setEcsManager(this);
    m_entities.emplace(name, ent);
    return m_entities[name];
}

std::unordered_map<std::string, std::shared_ptr<ecs::Entity>>& ecs::EcsManager::getEntities()
{
    return m_entities;
}