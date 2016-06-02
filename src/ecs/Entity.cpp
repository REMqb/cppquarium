#include "Entity.hpp"

using ecs::Entity;
using ecs::EntityComponentSystem;

Entity::Entity(EntityComponentSystem& ecs) : ecs(ecs){

}

Entity::~Entity(){

}
