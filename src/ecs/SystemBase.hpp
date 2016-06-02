#pragma once
#include <type_traits>
#include <memory>
#include <unordered_map>
#include <functional>

namespace ecs {
    class Entity;
}

namespace std {
    template<> struct hash<reference_wrapper<const ecs::Entity>>{
        using argument_type = reference_wrapper<const ecs::Entity>;
        using result_type = std::size_t;
        result_type operator()(argument_type const& s) const;
    };
}

namespace ecs{

bool operator==(const std::reference_wrapper<const ecs::Entity>& ref1, const std::reference_wrapper<const ecs::Entity>& ref2);

class EntityComponentSystem;
class Component;
template<typename, typename> class System;

class SystemBase{
        template<typename, typename> friend class System;
    public:
        /// Type of the stored components, declared here to have valid template in System
        using ComponentType = Component;
        /// Type of the system used as a base, declared here to have valid template in System
        using SystemBaseType = SystemBase;

        SystemBase() = delete;
        SystemBase(const SystemBase&) = delete;
        SystemBase(SystemBase&&) = default;

        SystemBase& operator=(const SystemBase&) = delete;
        SystemBase& operator=(SystemBase&&) = default;

        Component& attachComponentTo(const Entity& entity);
        Component* getAttachedComponentFor(const Entity& entity) const;

        size_t componentCount() const;

        virtual ~SystemBase() = 0;

    protected:
        EntityComponentSystem& ecs;
        std::unordered_map<std::reference_wrapper<const Entity>, std::unique_ptr<ComponentType>> componentsMap;

    private:
        SystemBase(EntityComponentSystem& ecs);

        virtual Component& doAttachComponentTo(const Entity& entity) = 0;

};

}
