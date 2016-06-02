#pragma once

#include "ecs/EntityComponentSystem.hpp"
#include "ecs/Component.hpp"

class FishSystem;
class GenderSystem;
class SeaweedSystem;

struct GenderComponent : public ecs::Component{
    GenderComponent(const ecs::Entity& entity);

    enum class Gender{
        MALE,
        FEMALE
    };

    GenderComponent& setGender(GenderComponent::Gender gender);

    Gender gender;
};


class Aquarium final{
    public:
        Aquarium();

        void populate();

        ecs::Entity& createFish(const std::string& name, GenderComponent::Gender gender);
        ecs::Entity& createSeaweed();

        void run();

    private:
        FishSystem* fishSystem;
        GenderSystem* genderSystem;
        SeaweedSystem* seaweedSystem;

        ecs::EntityComponentSystem ecs;
};
