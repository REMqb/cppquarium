#include "EventListenerManagerBase.hpp"

#include "../EntityComponentSystem.hpp"

namespace ecs {
    EventListenerManagerBase::EventListenerManagerBase(EntityComponentSystem& ecs){
        ecs.autoRegisterEventListenerManager(*this);
    }

    EventListenerManagerBase::~EventListenerManagerBase(){

    }
}
