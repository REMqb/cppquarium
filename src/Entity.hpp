#pragma once

class EntityComponentSystem;

class Entity final {
    public:
        Entity(EntityComponentSystem& ecs);

        Entity(const Entity&) = delete;
        Entity(Entity&&) = default;

        Entity& operator=(const Entity&) = delete;
        Entity& operator=(Entity&&) = default;

        ~Entity();

    private:
        EntityComponentSystem& ecs;

};
