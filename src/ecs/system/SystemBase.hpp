#pragma once
#include <type_traits>
#include <memory>
#include <unordered_map>
#include <functional>

#include "../EntityComponentSystem.hpp"

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

class Component;
template<typename> class System;

class SystemBase{
        template<typename> friend class System; // Only system can inherit SystemBase
    public:
        SystemBase() = delete;
        SystemBase(const SystemBase&) = delete;
        SystemBase(SystemBase&&) = default;

        SystemBase& operator=(const SystemBase&) = delete;
        SystemBase& operator=(SystemBase&&) = default;

        virtual ~SystemBase() = 0;

    protected:

        EntityComponentSystem& ecs;

    private:
        SystemBase(EntityComponentSystem& ecs);

};

}
