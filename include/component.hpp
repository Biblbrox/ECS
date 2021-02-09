#ifndef COMPONENT_HPP
#define COMPONENT_HPP

namespace ecs
{
    class EcsManager;

    /**
     * Base class for component
     */
    class Component
    {
    public:
        Component() : m_ecsManager(nullptr)
        {};

        virtual ~Component() = default;

        virtual void setEcsManager(EcsManager *ecs) final;

    private:
        EcsManager *m_ecsManager;
    };
}

#endif //COMPONENT_HPP
