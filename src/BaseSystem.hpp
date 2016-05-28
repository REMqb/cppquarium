#pragma once

namespace ecs{

class EntityComponentSystem;
class Component;

class BaseSystem
{
    public:
        BaseSystem(EntityComponentSystem& ecs);

        BaseSystem(const BaseSystem&) = delete;
        BaseSystem(BaseSystem&&) = default;

        BaseSystem& operator=(const BaseSystem&) = delete;
        BaseSystem& operator=(BaseSystem&&) = default;

        virtual ~BaseSystem() = 0;

    protected:

    private:

        EntityComponentSystem& ecs;

};

}
