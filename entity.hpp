#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <unordered_map>

#include "typelist.hpp"
#include "component.hpp"
#include "robin_hood.h"

namespace ecs
{

    typedef robin_hood::unordered_map<size_t, std::shared_ptr<Component>> ComponentMap;

    /**
     * Avoid circular including
     */
    class Component;

    /**
     * Entity class
     * Each entity may contain several unique components
     */
    class Entity
    {
    public:
        Entity(size_t id) : m_alive(false), m_id(id)
        {}

        ~Entity()
        {};

        Entity(Entity &&en) = default;

        Entity(Entity &en) = default;
        Entity(const Entity &en) = default;

        Entity &operator=(Entity &&) = default;

        Entity &operator=(const Entity &) = default;

        /**
         * Create new component and return it
         * ComponentType must be child of Component class
         * @tparam ComponentType
         * @return
         */
        template<class ComponentType>
        std::shared_ptr<Component> addComponent()
        {
            static_assert(std::is_base_of_v<Component, ComponentType>,
                          "Template parameter class must be child of Component");
            m_components[types::type_id<ComponentType>] =
                    std::static_pointer_cast<Component>(std::make_shared<ComponentType>());
            return m_components[types::type_id<ComponentType>];
        }

        /**
         * Create new component and return it
         * ComponentType must be child of Component class
         * @tparam ComponentType
         * @return
         */
        template<class ComponentType>
        std::shared_ptr<Component> addComponent(const ComponentType& comp)
        {
            m_components[types::type_id<ComponentType>] =
                    std::static_pointer_cast<Component>(
                            std::make_shared<ComponentType>(comp));
            return m_components[types::type_id<ComponentType>];
        }

        /**
         * Create new component
         * Each of ComponentTypes must be child of Component class
         * @tparam ComponentType
         * @return
         */
        template<class ...ComponentTypes>
        void addComponents()
        {
            static_assert(types::IsBaseOfRec<Component, types::TypeList<ComponentTypes...>>::value,
                          "Template parameter class must be child of Component");
            using ComponentList = types::TypeList<ComponentTypes...>;
            static_assert(types::Length<ComponentList>::value >= 2,
                          "Length of ComponentTypes must be greeter than 2");

            auto bin = [](auto x, auto y) { return 0; };

            auto un = [this](auto x) {
                m_components[types::type_id<decltype(x)>] =
                        std::static_pointer_cast<Component>(std::make_shared<decltype(x)>());
                return 0;
            };

            types::typeListReduce<ComponentList>(un, bin);
        }


        /**
         * Get component iterator by type
         * @tparam ComponentType
         * @return
         */
        template<class ComponentType>
        ComponentMap::iterator getComponentIt()
        {
            static_assert(std::is_base_of_v<Component, ComponentType>,
                          "Template parameter class must be child of Component");
            auto it = m_components.find(types::type_id<ComponentType>);
            return it;
        }

        /**
         * Get component by type
         * @tparam ComponentType
         * @return
         */
        template<class ComponentType>
        std::shared_ptr<ComponentType> getComponent()
        {
            static_assert(std::is_base_of_v<Component, ComponentType>,
                          "Template parameter class must be child of Component");

            const auto& it = m_components.find(types::type_id<ComponentType>);
            if (it == m_components.end())
                return std::shared_ptr<ComponentType>(nullptr);

            return std::dynamic_pointer_cast<ComponentType>(it->second);
        }

        /**
       * Get component by type
       * @tparam ComponentType
       * @return
       */
        template<class ComponentType>
        std::shared_ptr<const ComponentType> getComponent() const
        {
            static_assert(std::is_base_of_v<Component, ComponentType>,
                          "Template parameter class must be child of Component");

            const auto& it = m_components.find(types::type_id<ComponentType>);
            if (it == m_components.end())
                return std::shared_ptr<const ComponentType>(nullptr);

            return std::dynamic_pointer_cast<const ComponentType>(it->second);
        }

        /**
         * Get component by type or insert if doesn't exists.
         * @tparam ComponentType
         * @return
         */
        template<class ComponentType>
        std::shared_ptr<ComponentType> getComponentNew()
        {
            static_assert(std::is_base_of_v<Component, ComponentType>,
                          "Template parameter class must be child of Component");

            return std::dynamic_pointer_cast<ComponentType>(m_components[types::type_id<ComponentType>]);
        }

        template<class ComponentType>
        void removeComponent()
        {
            static_assert(std::is_base_of_v<Component, ComponentType>,
                          "Template parameter class must be child of Component");

            auto it = m_components.find(types::type_id<ComponentType>);
            if (it != m_components.end())
                m_components.erase(it);
        }

        const ComponentMap& getComponents() const
        {
            return m_components;
        }

        void activate() noexcept
        {
            m_alive = true;
        }

        bool isActivate() const noexcept
        {
            return m_alive;
        }

        size_t getId() const noexcept
        {
            return m_id;
        }

        void setId(size_t id) noexcept
        {
            m_id = id;
        }

        void kill() noexcept
        {
            m_alive = false;
        }

        std::string& name()
        {
            return m_name;
        }

    private:
        ComponentMap m_components;
        bool m_alive;
        size_t m_id;
        std::string m_name;
    };
};

#endif //ENTITY_HPP
