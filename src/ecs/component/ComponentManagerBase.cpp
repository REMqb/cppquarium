#include "ComponentManagerBase.hpp"

#include "../EntityComponentSystem.hpp"

namespace ecs {
    ComponentManagerBase::ComponentManagerBase(EntityComponentSystem& ecs){
        ecs.autoRegisterComponentManager(*this);
    }

    ComponentManagerBase::~ComponentManagerBase(){

    }
}
