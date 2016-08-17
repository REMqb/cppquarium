#pragma once

namespace ecs {

class Entity;

/**
 * @brief The BaseComponent struct
 * Base struct (class) for components.
 * Components should only contain data, no methods.
 */
struct Component{
    public:
        const Entity& entity;

    protected:
        Component(const Entity& entity);

        Component(const Component&) = delete;
        Component(Component&&) = default;

        Component& operator=(const Component&) = delete;
        Component& operator=(Component&&) = default;
};

}
