#include "EntityComponentSystem.hpp"

#include "Entity.hpp"
#include "system/SystemBase.hpp"

using std::make_unique;
using ecs::EntityComponentSystem;
using ecs::Entity;
using ecs::SystemBase;

EntityComponentSystem::EntityComponentSystem(){
}

Entity& EntityComponentSystem::createEntity(){
    entities.push_back(make_unique<Entity>(*this));

    return *entities.back();
}

void EntityComponentSystem::autoRegisterComponentManager(ComponentManagerBase& componentManager){
    componentManagers.emplace_back(componentManager);
}

void EntityComponentSystem::autoRegisterEventListenerManager(EventListenerManagerBase& eventListenerManager){
    eventListenerManagers.emplace_back(eventListenerManager);
}

EntityComponentSystem::~EntityComponentSystem(){
}

/*using hash = std::hash<std::reference_wrapper<const EntityComponentSystem>>;

template<>
hash::result_type hash::operator()(const std::reference_wrapper<const EntityComponentSystem>& s) const noexcept{
    return std::hash<const EntityComponentSystem*>()(&s.get());
}*/

namespace std {
//template<>
    size_t hash<std::reference_wrapper<EntityComponentSystem>>::operator()(const std::reference_wrapper<EntityComponentSystem> &s) const noexcept{
        return std::hash<EntityComponentSystem*>()(&s.get());
    }
}
