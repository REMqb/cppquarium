#pragma once

#include "SystemBase.hpp"
#include "EntityComponentSystem.hpp"

#include <unordered_map>
#include <memory>
#include <functional>

namespace ecs {

template<typename SystemT>
class System : public SystemBase {
    public:
        System(EntityComponentSystem& ecs) : SystemBase(ecs) {};

        template<typename EventT, typename... Args> void fireEvent(Args&&... args);
        template<typename EventT> void addListener(std::function<void(EventT&)> listener);

        ~System() = 0;

    protected:

    private:
};

template<typename SystemT>
System<SystemT>::~System(){
}

template<typename SystemT>
template<typename EventT, typename... Args> void System<SystemT>::fireEvent(Args&&... args){
    EventT event(*static_cast<SystemT*>(this), std::forward<Args>(args)...);

    ecs.fireEvent(event);
}

template<typename SystemT>
template<typename EventT> void System<SystemT>::addListener(std::function<void(EventT&)> listener){
    ecs.addListener(static_cast<SystemT*>(this), listener); // CRTP cast
}

}

