#pragma once

#include "ecs/system/System.hpp"
#include "ecs/event/Event.hpp"

class TickSystem : public ecs::System<TickSystem> {
    public:
        class TickEvent : public ecs::Event<TickSystem>{
            public:
                TickEvent(TickSystem& tickSystem) : Event(tickSystem){}
        };

        TickSystem(ecs::EntityComponentSystem& ecs);

        void tick();

    private:
        unsigned long long currentTick = 1; // start at one because 0 is initial value in interested targets
};
