#include "TickSystem.hpp"

TickSystem::TickSystem(ecs::EntityComponentSystem& ecs) : System(ecs){

}

void TickSystem::tick(){
    fireEvent<TickEvent>();

    currentTick++;
}
