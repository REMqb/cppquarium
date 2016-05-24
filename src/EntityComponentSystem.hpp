#pragma once

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <memory>
#include <vector>

class System;
class Entity;

class EntityComponentSystem {
    public:
        EntityComponentSystem();

        Entity& createEntity();

    private:
        std::unordered_map<std::type_index, std::unique_ptr<System>> systems;
        std::vector<std::unique_ptr<Entity>> entities;
};
