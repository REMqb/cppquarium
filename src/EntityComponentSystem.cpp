#include "EntityComponentSystem.hpp"

#include "Entity.hpp"
#include "BaseSystem.hpp"

using std::make_unique;
using ecs::EntityComponentSystem;
using ecs::Entity;
using ecs::BaseSystem;

EntityComponentSystem::EntityComponentSystem(){
}

Entity& EntityComponentSystem::createEntity(){
    entities.push_back(make_unique<Entity>(*this));

    return *entities.back();
}

EntityComponentSystem::~EntityComponentSystem(){
}
