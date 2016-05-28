#pragma once

#include "EntityComponentSystem.hpp"

class FishSystem;
class SeaweedSystem;

class Aquarium final{
    public:
        Aquarium();

        void populate();
        void run();

    private:
        FishSystem* fishSystem;
        SeaweedSystem* seaweedSystem;

        ecs::EntityComponentSystem ecs;
};
