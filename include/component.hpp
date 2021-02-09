#ifndef COMPONENT_HPP
#define COMPONENT_HPP

namespace ecs
{
    class CesManager;

    /**
     * Base class for component
     */
    class Component
    {
    public:
        Component() : m_cesManager(nullptr)
        {};

        virtual ~Component() = default;

        virtual void setCesManager(CesManager *cesMan) final;

    private:
        CesManager *m_cesManager;
    };
}

#endif //COMPONENT_HPP
