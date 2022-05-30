#ifndef ECSMANAGER_HPP
#define ECSMANAGER_HPP

#include <crossguid/guid.hpp>
#include <string>

#include "basesystem.hpp"
#include "entity.hpp"

namespace ecs {
/**
 * ecs manager class.
 * It must create systems and update them
 * This also used by systems to fetch entities
 */
class EcsManager {
  public:
    using EntityNames = std::unordered_map<std::string, size_t>;
    using Entities = std::unordered_map<size_t, std::shared_ptr<Entity>>;
    using Systems = std::unordered_map<size_t, std::shared_ptr<BaseSystem>>;

    /**
     * Create systems, etc...
     */
    virtual void init() = 0;

    /**
     * Create systems, etc...
     */
    virtual void init(const std::string &init_file) = 0;

    virtual void addEntityFromFile(const std::string &model_file) = 0;

    virtual int genUniqueId() const noexcept
    {
        static int id = 0;
        return id++;
    }

    virtual std::string genUniqueName() const noexcept
    {
        return xg::newGuid().str();
    }

    /**
     * Update systems
     * @param delta
     */
    virtual void update(size_t delta) = 0;

    virtual std::shared_ptr<Entity> createEntity(size_t name)
    {
        std::shared_ptr ent = std::make_shared<Entity>(name);
        m_entities.emplace(name, ent);
        m_entityByNames.emplace(xg::newGuid().str(), name);
        return m_entities[name];
    }

    template <typename SystemType> SystemType &createSystem()
    {
        static_assert(std::is_base_of_v<BaseSystem, SystemType>,
                      "Template parameter class must be child of BaseSystem");

        std::shared_ptr<SystemType> system(new SystemType());
        system->setEcsManager(this);
        m_systems.insert(
            {types::type_id<SystemType>, std::static_pointer_cast<BaseSystem>(system)});
        return *system;
    }

    virtual std::unordered_map<size_t, std::shared_ptr<Entity>> &getEntities()
    {
        return m_entities;
    }

    virtual std::unordered_map<std::string, size_t> &getEntityByNames()
    {
        return m_entityByNames;
    }

  protected:
    Entities m_entities;
    EntityNames m_entityByNames;
    Systems m_systems;
};
}; // namespace ecs

#endif // ECSMANAGER_HPP
