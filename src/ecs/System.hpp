#pragma once

#include "SystemBase.hpp"
#include "EntityComponentSystem.hpp"
#include "CovariantComponentMap.hpp"

#include <unordered_map>
#include <memory>
#include <functional>

namespace ecs {

template<typename ComponentOrSystemTypeT, typename ComponentTypeT = void>
class System : public
        std::conditional<
            std::is_base_of<SystemBase, ComponentOrSystemTypeT>::value,
            ComponentOrSystemTypeT, // ComponentOrSystemTypeT is system SubType
            SystemBase              // ComponentOrSystemTypeT ins't system SubType
        >::type {
    public:
        /// Type of the system used as a base, SystemBase if ComponentOrSystemTypeT isn't derived from SystemBase, ComponentOrSystemTypeT otherwise.
        using SystemBaseType = typename std::conditional<
            std::is_base_of<SystemBase, ComponentOrSystemTypeT>::value,
            ComponentOrSystemTypeT, // ComponentOrSystemTypeT is system SubType
            SystemBase              // ComponentOrSystemTypeT ins't system SubType
        >::type;
        /// Type of the stored components, ComponentTypeT if ComponentTypeT is derived from Component else ComponentOrSystemTypeT if ComponentOrSystemTypeT is derived from Component, SystemBaseType::ComponentType otherwise.
        using ComponentType = typename std::conditional<
            std::is_base_of<Component, ComponentTypeT>::value,
            ComponentTypeT,
            typename std::conditional<
                std::is_base_of<Component, ComponentOrSystemTypeT>::value,
                ComponentOrSystemTypeT,
                typename SystemBaseType::ComponentType
            >::type
        >::type;

        System(EntityComponentSystem& ecs);

        ComponentType& attachComponentTo(const Entity& entity);
        ComponentType* getAttachedComponentFor(const Entity& entity) const;

    protected:
        std::unique_ptr<ComponentType> createComponent();

        //std::unordered_map<std::reference_wrapper<const Entity>, std::unique_ptr<ComponentType>> entityComponentMap;
        CovariantComponentMap<true, typename detail::ComponentsFromSystem<System<ComponentOrSystemTypeT, ComponentTypeT>>::type> entityComponentMap;

    private:
        virtual ComponentType& doAttachComponentTo(const Entity& entity) override;
};

template<typename ComponentOrSystemTypeT, typename ComponentTypeT> System<ComponentOrSystemTypeT, ComponentTypeT>::System(EntityComponentSystem& ecs) : SystemBaseType(ecs){
}

template<typename ComponentOrSystemTypeT, typename ComponentTypeT> typename System<ComponentOrSystemTypeT, ComponentTypeT>::ComponentType& System<ComponentOrSystemTypeT, ComponentTypeT>::attachComponentTo(const Entity& entity){
    return doAttachComponentTo(entity);
}

template<typename ComponentOrSystemTypeT, typename ComponentTypeT> typename System<ComponentOrSystemTypeT, ComponentTypeT>::ComponentType* System<ComponentOrSystemTypeT, ComponentTypeT>::getAttachedComponentFor(const Entity& entity) const{
    auto it = this->componentsMap.find(entity);

    if(it != this->componentsMap.end()){
        return static_cast<ComponentType*>(it->second.get());
    }else{
        return nullptr;
    }
}

template<typename ComponentOrSystemTypeT, typename ComponentTypeT> typename System<ComponentOrSystemTypeT, ComponentTypeT>::ComponentType& System<ComponentOrSystemTypeT, ComponentTypeT>::doAttachComponentTo(const Entity& entity) {
    auto ptr = std::make_unique<ComponentType>(entity);
    ComponentType& ref = *ptr;

    this->componentsMap.emplace(entity, std::move(ptr));

    return ref;
}

}

