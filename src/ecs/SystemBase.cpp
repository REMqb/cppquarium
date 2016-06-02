#include "SystemBase.hpp"

#include "Component.hpp"
#include "Entity.hpp"

using ecs::SystemBase;
using ecs::EntityComponentSystem;
using ecs::Component;
using ecs::Entity;

using std::reference_wrapper;

using hash = std::hash<std::reference_wrapper<const Entity>>;

hash::result_type hash::operator()(argument_type const& s) const{
    return std::hash<const Entity*>()(&s.get());
}

bool ecs::operator==(const reference_wrapper<const ecs::Entity>& ref1, const reference_wrapper<const ecs::Entity>& ref2){
    return &ref1.get() == &ref2.get();
}

SystemBase::SystemBase(EntityComponentSystem& ecs) : ecs(ecs) {

}

Component& SystemBase::attachComponentTo(const Entity& entity){
    return doAttachComponentTo(entity);
}

Component* SystemBase::getAttachedComponentFor(const Entity& entity) const{
    auto it = componentsMap.find(entity);

    if(it != componentsMap.end()){
        return it->second.get();
    }else{
        return nullptr;
    }
}

size_t SystemBase::componentCount() const{
    return componentsMap.size();
}

SystemBase::~SystemBase(){

}
