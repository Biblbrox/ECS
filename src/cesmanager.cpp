#include <memory>

#include "cesmanager.hpp"

std::shared_ptr<ecs::Entity> ecs::CesManager::createEntity(const std::string& name)
{
    std::shared_ptr ent = std::make_shared<Entity>();
    ent->setCesManager(this);
    m_entities.emplace(name, ent);
    return m_entities[name];
}

std::unordered_map<std::string, std::shared_ptr<ecs::Entity>>& ecs::CesManager::getEntities()
{
    return m_entities;
}