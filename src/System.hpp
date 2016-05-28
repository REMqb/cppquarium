#pragma once

#include "BaseSystem.hpp"
#include "EntityComponentSystem.hpp"

namespace ecs {

//class EntityComponentSystem;

template <typename BaseComponentType>
class System : public BaseSystem
{
    public:
        System(EntityComponentSystem& ecs) : BaseSystem(ecs){
            ecs.registerComponentProvider(*this);
        }
};

}

