#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include <iostream>

#include "StaticMapHandler.hpp"

#include "ComponentManagerBase.hpp"

namespace ecs {
    class Entity;
    class EntityComponentSystem;

    template<typename ComponentT>
    class ComponentManager final : public ComponentManagerBase {
        public:

            template<typename... Args>
            ComponentT& attachComponentTo(Entity& entity, Args&&... args);

            /////// STATICS ///////

            static ComponentManager<ComponentT>& getComponentManagerFor(EntityComponentSystem& ecs);
        private:
            std::unordered_map<std::reference_wrapper<const Entity>, ComponentT> components;

            /////// STATICS ///////

            static std::unordered_map<std::reference_wrapper<EntityComponentSystem>, ComponentManager<ComponentT>>& componentManagers;
    };

    template<typename ComponentT>
    template<typename... Args>
    ComponentT& ComponentManager<ComponentT>::attachComponentTo(Entity& entity, Args&&... args){
        auto result = components.emplace(std::piecewise_construct, std::forward_as_tuple<Entity&>(entity), std::forward_as_tuple<Entity&, Args...>(entity, std::forward<Args>(args)...));

        return result.first->second;
    }

    template<typename ComponentT>
    ComponentManager<ComponentT>& ComponentManager<ComponentT>::getComponentManagerFor(EntityComponentSystem& ecs){
        return componentManagers[ecs];
    }

    template<typename ComponentT>
    std::unordered_map<std::reference_wrapper<EntityComponentSystem>, ComponentManager<ComponentT>>& ComponentManager<ComponentT>::componentManagers = StaticMapHandler<std::reference_wrapper<EntityComponentSystem>, ComponentManager<ComponentT>>::getMap();

}
