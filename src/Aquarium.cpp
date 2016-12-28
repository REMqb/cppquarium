#include "Aquarium.hpp"

#include <iostream>

#include "ecs/system/System.hpp"
#include "ecs/component/Component.hpp"
#include "ecs/Entity.hpp"
#include "TickSystem.hpp"

using namespace std;
using namespace ecs;

struct FishComponent : public Component{
    template<typename NameT>
    FishComponent(const Entity& entity, NameT&& name): Component(entity), name(std::forward<NameT>(name)){}

    string name;

    FishComponent& setName(const string& name){
        this->name = name;

        return *this;
    }
};



struct SeaweedComponent: public Component{
    SeaweedComponent(const Entity& entity): Component(entity){}

    SeaweedComponent(const SeaweedComponent&) = delete;
    SeaweedComponent(SeaweedComponent&&) = default;

    SeaweedComponent& operator=(const SeaweedComponent&) = delete;
    SeaweedComponent& operator=(SeaweedComponent&&) = default;

    ~SeaweedComponent(){cout << __PRETTY_FUNCTION__ << endl;}
};

GenderComponent::GenderComponent(const Entity& entity): Component(entity){

}

GenderComponent& GenderComponent::setGender(Gender gender){
    this->gender = gender;

    return *this;
}

class GenderSystem : public System<GenderSystem>{
    public:

        GenderSystem(EntityComponentSystem& ecs) : System(ecs){
            ecs.getSystem<TickSystem>()->addListener<TickSystem::TickEvent>(std::bind(&GenderSystem::onTick, this, std::placeholders::_1));
        }

        void onTick(TickSystem::TickEvent& event){
            (void)event;
            cout << "tick" << endl;
        }
};

class FishSystem : public System<FishSystem>{
    private:
        std::unordered_map<reference_wrapper<Entity>, std::tuple<reference_wrapper<FishComponent>, GenderComponent*>> fishes;

    public:

        FishSystem(EntityComponentSystem& ecs): System(ecs), fishes{}{
            ecs.addListener<EntityComponentSystem::ComponentAttachedEvent<FishComponent>>(std::bind(&FishSystem::onFishComponentAdded, this, std::placeholders::_1));
        }

        void onFishComponentAdded(EntityComponentSystem::ComponentAttachedEvent<FishComponent>& event){
            fishes.emplace(std::piecewise_construct, std::forward_as_tuple(event.getAttachedOn()), std::forward_as_tuple(event.getAttachedComponent(), nullptr));
        }

        void printFishes(){
            //GenderSystem* genderSystem = ecs.getSystem<GenderSystem>();

            //size_t n = 1;
            /*for(const auto& fish : componentsMap){
                const FishComponent& fishComponent = static_cast<const FishComponent&>(*fish.second);
                GenderComponent* genderComponent{nullptr};
                if(genderSystem) {
                    genderComponent = genderSystem->getAttachedComponentFor(fishComponent.entity);
                }

                string genre{"inconnu"};

                if(genderComponent){
                    switch (genderComponent->gender) {
                        case GenderComponent::Gender::MALE:
                            genre = "mâle";
                            break;
                        case GenderComponent::Gender::FEMALE:
                            genre = "femelle";
                            break;
                    }
                }

                cout << "Poisson #" << n << " : nom = " << fishComponent.name << ", genre = " << genre << endl;

                n++;
            }*/
        }
};

class SeaweedSystem : public System<SeaweedSystem>{
    public:
        SeaweedSystem(EntityComponentSystem& ecs):System(ecs){

        }


};

Aquarium::Aquarium() {
    cout << "Initializing the aquarium... " << flush;

    tickSystem = &ecs.registerSystem<TickSystem>();

    fishSystem = &ecs.registerSystem<FishSystem>();
    genderSystem = &ecs.registerSystem<GenderSystem>();
    seaweedSystem = &ecs.registerSystem<SeaweedSystem>();

    cout << "[Done]" << endl;
}

void Aquarium::populate(){
    cout << "Populating... " << flush;

    createFish("toto", GenderComponent::Gender::MALE);
    createFish("tata", GenderComponent::Gender::FEMALE);
    createSeaweed();
    createSeaweed();
    createSeaweed();

    cout << "[Done]" << endl;
}

Entity& Aquarium::createFish(const std::string& name, GenderComponent::Gender gender){
    Entity& entity = ecs.createEntity();

    entity.attachComponent<FishComponent>(name);
    entity.attachComponent<GenderComponent>().setGender(gender);

    return entity;
}

Entity& Aquarium::createSeaweed(){
    Entity& entity = ecs.createEntity();

    entity.attachComponent<SeaweedComponent>();

    return entity;
}

void Aquarium::run(){
    cout << "\nBegin Run" << endl;

    size_t i;
    //while(true){
    for(i = 0; i < 10; i++){
        cout << "> Step #" << (i + 1) << endl;

        tickSystem->tick();

        //cout << "Il y a " << seaweedSystem->componentCount() << " algue(s) et " << fishSystem->componentCount() << " poisson(s)." << endl;

        fishSystem->printFishes();
        //i++;
    }
}
