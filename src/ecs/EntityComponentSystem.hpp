#pragma once

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <memory>
#include <vector>
//#include <type_traits>
#include <cassert>

#include <utility>


#include "event/EventListenerManagerBase.hpp"
#include "event/EventListenerManager.hpp"

#include "component/ComponentManagerBase.hpp"
#include "component/ComponentManager.hpp"

namespace ecs {

class SystemBase;
template<typename> class System;
template<typename> class Event;
class Component;
class Entity;

/**
 * @brief The EntityComponentSystem class manage own entities and systems.
 */
class EntityComponentSystem final {
        friend ComponentManagerBase;
        friend EventListenerManagerBase;
    public:
        EntityComponentSystem();

        Entity& createEntity();

        /**
         * @brief Register a system and return its instance, if it's already registered (either as an instance of it or an alias) return the existing instance without creating a new one.
         */
        template<typename SystemType, typename... Args> SystemType& registerSystem(Args&&... args);
        /**
         * @brief Register the type AliasType as an Alias for the system of type SystemType.
         * Validity of the cast is checked via RTTI (dynamic_cast), if it's not valid (or SystemType isn't already registered) the program will crash (assert fail).
         * Assertions will be replaced by exceptions later.
         */
        template<typename SystemType, typename AliasType> void registerSystemAlias();
        /**
         * @brief Get the system of type SystemType, if it isn't registered, return null.
         */
        template<typename SystemType> SystemType* getSystem() const;

        template<typename EventT>
        void addListener(typename EventT::SourceT* source, std::function<void(EventT&)> listener);

        template<typename EventT>
        void fireEvent(EventT& event);

        template<typename ComponentT, typename... Args>
        ComponentT& attachComponentTo(Entity& entity, Args&&... args);

        ~EntityComponentSystem(); // we must define the destructor, otherwise the compiler can't create the default deleter for unique_ptr because System and Entity are forward declared (incomplete)

    private:

        /**
         * @brief internal member that register AliasType as an alias for the given system.
         */
        template<typename AliasType> void registerSystemAlias(SystemBase& system);

        void autoRegisterComponentManager(ComponentManagerBase& componentManager);
        void autoRegisterEventListenerManager(EventListenerManagerBase& eventListenerManager);

        /// map typeid to a system of the systems vector.
        std::unordered_map<std::type_index, std::reference_wrapper<SystemBase>> typeToSystemMap;
        /// map event typeid to the corresponding listener manager.
        //std::unordered_map<std::type_index, std::unique_ptr<EventListenerManagerBase>> eventListenerManagersMap;
        std::vector<std::reference_wrapper<EventListenerManagerBase>> eventListenerManagers;
        ///
        //std::unordered_map<std::type_index, std::unique_ptr<ComponentManagerBase>> componentManagersMap;
        std::vector<std::reference_wrapper<ComponentManagerBase>> componentManagers;
        /// vector holding systems
        std::vector<std::unique_ptr<SystemBase>> systems;
        /// vector holding entities, may be changed to another container type later.
        std::vector<std::unique_ptr<Entity>> entities;
};

template<typename SystemType, typename... Args>
SystemType& EntityComponentSystem::registerSystem(Args&&... args){
    static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemType must be derived from class System");

    SystemType* systemPtr;

    if(!(systemPtr = getSystem<SystemType>())){
        systems.emplace_back(std::make_unique<SystemType>(*this, std::forward<Args>(args)...));

        systemPtr = static_cast<SystemType*>(systems.back().get()); // static_cast is fine since it's the system we just created though not thread safe

        registerSystemAlias<SystemType>(*systemPtr);
    }

    return *systemPtr;
}

template<typename SystemType, typename AliasType>
void EntityComponentSystem::registerSystemAlias(){
    static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemType must be derived from class System");
    SystemType* system = getSystem<SystemType>();

    if(system){
        AliasType* casted = dynamic_cast<AliasType*>(system); // dynamic_cast to be sure the static cast in get will be valid.

        if(casted){
            registerSystemAlias<AliasType>(*casted);
        }else{
            assert(casted);
            //throw error (downcast impossible)
        }
    }else{
        assert(system);
        //throw error (base not registered)
    }
}

template<typename SystemType>
SystemType* EntityComponentSystem::getSystem() const{
    static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemType must be derived from class System");
    auto result = typeToSystemMap.find(typeid(SystemType));

    if(result == typeToSystemMap.end()){
        return nullptr;
    }else{
        return static_cast<SystemType*>(&result->second.get()); // static_cast is fine since it was registered either with that typeid or aliased with a valid downcast.
    }

}

template <typename AliasType>
inline void EntityComponentSystem::registerSystemAlias(SystemBase& system){
    typeToSystemMap.emplace(typeid(AliasType), system);
}

template<typename EventT>
void EntityComponentSystem::addListener(typename EventT::SourceT* source, std::function<void(EventT&)> listener){
    static_assert(std::is_base_of<Event<typename EventT::SourceT>, EventT>::value, "Event type must derive from Event"); // is it that nececary ?

    /*auto result = eventListenerManagersMap.find(typeid(EventT));

    EventListenerManager<EventT, typename EventT::SourceT>* manager = nullptr;

    if(result == eventListenerManagersMap.end()){
        auto ptr = std::make_unique<EventListenerManager<EventT, typename EventT::SourceT>>();

        manager = ptr.get();

        eventListenerManagersMap.emplace(typeid(EventT), std::move(ptr));
    }else{
        manager = static_cast<decltype(manager)>(result->second.get());
    }

    manager->addListener(source, listener);*/

    EventListenerManager<EventT, typename EventT::SourceT>::getEventListenerManagerFor(*this).addListener(source, listener);
}

template<typename EventT>
void EntityComponentSystem::fireEvent(EventT& event){
    /*auto result = eventListenerManagersMap.find(typeid(EventT));

    EventListenerManager<EventT, typename EventT::SourceT>* manager = nullptr;

    if(result != eventListenerManagersMap.end()){
        manager = static_cast<decltype(manager)>(result->second.get());

        manager->dispatchEvent(event);
    }*/

    EventListenerManager<EventT, typename EventT::SourceT>::getEventListenerManagerFor(*this).dispatchEvent(event);
}

template<typename ComponentT, typename... Args>
ComponentT& EntityComponentSystem::attachComponentTo(Entity& entity, Args&&... args){
    /*auto result = componentManagersMap.find(typeid(ComponentT));

    ComponentManager<ComponentT>* manager = nullptr;

    if(result == componentManagersMap.end()){
        auto ptr = std::make_unique<ComponentManager<ComponentT>>();

        manager = ptr.get();

        componentManagersMap.emplace(typeid(ComponentT), std::move(ptr));
    }else{
        manager = static_cast<decltype(manager)>(result->second.get());
    }*/

    return ComponentManager<ComponentT>::getComponentManagerFor(*this).attachComponentTo(entity, std::forward<Args>(args)...);
}

template <typename T>
bool operator==(const std::reference_wrapper<T>& ref1, const std::reference_wrapper<T>& ref2);

template <typename T>
bool operator==(const std::reference_wrapper<T>& ref1, const std::reference_wrapper<T>& ref2){
    return &ref1.get() == &ref2.get();
}


}

namespace std {
template<>
class hash<std::reference_wrapper<ecs::EntityComponentSystem>> {
public:
    size_t operator()(const std::reference_wrapper<ecs::EntityComponentSystem> &s) const noexcept;
};
}

