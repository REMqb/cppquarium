#pragma once

#include "EntityComponentSystem.hpp"

namespace ecs {

class Entity final {
    public:
        Entity(EntityComponentSystem& ecs);

        Entity(const Entity&) = delete;
        Entity(Entity&&) = default;

        Entity& operator=(const Entity&) = delete;
        Entity& operator=(Entity&&) = default;

        ~Entity();

        template<typename ComponentT, typename... Args> ComponentT& attachComponent(Args&&... args);

    private:
        EntityComponentSystem& ecs;

};

template<typename ComponentT, typename... Args> ComponentT& Entity::attachComponent(Args&&... args){
    return ecs.attachComponentTo<ComponentT>(*this, std::forward<Args>(args)...);
}

}
