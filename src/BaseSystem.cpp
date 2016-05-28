#include "BaseSystem.hpp"

using ecs::BaseSystem;
using ecs::EntityComponentSystem;

BaseSystem::BaseSystem(EntityComponentSystem& ecs) : ecs(ecs) {

}

BaseSystem::~BaseSystem(){

}
