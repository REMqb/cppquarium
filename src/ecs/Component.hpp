#pragma once

namespace ecs {

class Entity;

/**
 * @brief The BaseComponent struct
 * Base struct (class) for components, should only contain data, no methods.
 */
struct Component{
    public:
        const Entity& entity;

    protected:
        Component(const Entity& entity);
};

}
