#include "EntityComponentSystem.hpp"

using std::make_unique;

EntityComponentSystem::EntityComponentSystem()
{

}

Entity& EntityComponentSystem::createEntity(){
    entities.push_back(make_unique<Entity>());

    return *entities.back();
}
