#pragma once

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <memory>
#include <vector>
//#include <type_traits>
#include <cassert>
#include <boost/any.hpp>

namespace ecs {

class SystemBase;
template<typename> class System;
class Component;
class Entity;

/**
 * @brief The EntityComponentSystem class manage own entities and systems.
 */
class EntityComponentSystem final {
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

        //template<typename ComponentType> void registerComponentProvider(System<ComponentType>& system);

        //template<typename ComponentType, typename AliasComponentType, typename SystemType> void registerComponentProviderAlias(SystemType& system);



        ~EntityComponentSystem(); // we must define the destructor, otherwise the compiler can't create the default deleter for unique_ptr because System and Entity are forward declared (incomplete)

    private:

        /**
         * @brief internal member that register AliasType as an alias for the given system.
         */
        template<typename AliasType> void registerSystemAlias(SystemBase& system);

        /// map typeid to a system of the systems vector.
        std::unordered_map<std::type_index, std::reference_wrapper<SystemBase>> typeToSystemMap;
        /// vector holding systems
        std::vector<std::unique_ptr<SystemBase>> systems;
        /// vector holding entities, may be changed to another container type later.
        std::vector<std::unique_ptr<Entity>> entities;
};

template<typename SystemType, typename... Args> SystemType& EntityComponentSystem::registerSystem(Args&&... args){
    static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemType must be derived from class System");

    SystemType* systemPtr;

    if(!(systemPtr = getSystem<SystemType>())){
        systems.emplace_back(std::make_unique<SystemType>(*this, std::forward<Args...>(args...)));

        systemPtr = static_cast<SystemType*>(systems.back().get()); // static_cast is fine since it's the system we just created though not thread safe

        registerSystemAlias<SystemType>(*systemPtr);
    }

    return *systemPtr;
}

template<typename SystemType, typename AliasType> void EntityComponentSystem::registerSystemAlias(){
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

template<typename SystemType> SystemType* EntityComponentSystem::getSystem() const{
    static_assert(std::is_base_of<SystemBase, SystemType>::value, "SystemType must be derived from class System");
    auto result = typeToSystemMap.find(typeid(SystemType));

    if(result == typeToSystemMap.end()){
        return nullptr;
    }else{
        return static_cast<SystemType*>(&result->second.get()); // static_cast is fine since it was registered either with that typeid or aliased with a valid downcast.
    }

}

template <typename AliasType> inline void EntityComponentSystem::registerSystemAlias(SystemBase& system){
    typeToSystemMap.emplace(typeid(AliasType), system);
}

/*template<typename ComponentType> void EntityComponentSystem::registerComponentProvider(System<ComponentType>& system){
    static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "BaseComponent must be derived from class BaseComponent");

    componentProvider.emplace(typeid(ComponentType), system);
}*/

}
