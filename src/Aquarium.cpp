#include "Aquarium.hpp"

#include <iostream>

#include "ecs/System.hpp"
#include "ecs/Component.hpp"

using namespace std;
using namespace ecs;

struct FishComponent : public Component{
    FishComponent(const Entity& entity): Component(entity){}

    string name;

    FishComponent& setName(const string& name){
        this->name = name;

        return *this;
    }
};



struct SeaweedComponent: public Component{
    SeaweedComponent(const Entity& entity): Component(entity){}
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

        }
};

class FishSystem : public System<FishSystem>{
    public:

        FishSystem(EntityComponentSystem& ecs):System(ecs){
        }

        void printFishes(){
            GenderSystem* genderSystem = ecs.getSystem<GenderSystem>();

            size_t n = 1;
            for(const auto& fish : componentsMap){
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
            }
        }
};

class SeaweedSystem : public System<SeaweedComponent>{
    public:
        SeaweedSystem(EntityComponentSystem& ecs):System(ecs){

        }

};

Aquarium::Aquarium() {
    cout << "Initializing the aquarium... " << flush;

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

    fishSystem->attachComponentTo(entity).setName(name);
    genderSystem->attachComponentTo(entity).setGender(gender);

    /*FishComponent& fishComponent = fishSystem->attachComponentTo(entity);
    GenderComponent& genderComponent = genderSystem->attachComponentTo(entity);

    fishComponent.name = name;
    genderComponent.gender = gender;*/

    return entity;
}

Entity& Aquarium::createSeaweed(){
    Entity& entity = ecs.createEntity();

    seaweedSystem->attachComponentTo(entity);

    return entity;
}

void Aquarium::run(){
    cout << "\nBegin Run" << endl;

    size_t i;
    //while(true){
    for(i = 0; i < 10; i++){
        cout << "> Step #" << (i + 1) << endl;

        cout << "Il y a " << seaweedSystem->componentCount() << " algue(s) et " << fishSystem->componentCount() << " poisson(s)." << endl;

        fishSystem->printFishes();
        //i++;
    }
}
