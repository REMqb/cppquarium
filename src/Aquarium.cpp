#include "Aquarium.hpp"

#include <iostream>

#include "System.hpp"
#include "BaseComponent.hpp"

using namespace std;
using namespace ecs;

class FishComponent : public BaseComponent{

};

class FishSystem : public System<FishComponent>{
    public:

        FishSystem(EntityComponentSystem& ecs):System(ecs){
        }
};

class SeaweedSystem : public BaseSystem{
    public:
        SeaweedSystem(EntityComponentSystem& ecs):BaseSystem(ecs){

        }

};

Aquarium::Aquarium() {
    cout << "Initializing the aquarium... " << flush;

    fishSystem = &ecs.registerSystem<FishSystem>();
    seaweedSystem = &ecs.registerSystem<SeaweedSystem>();

    cout << "[Done]" << endl;
}

void Aquarium::populate(){
    cout << "Populating... " << flush;


    cout << "[Done]" << endl;
}

void Aquarium::run(){
    cout << "\nBegin Run" << endl;

    size_t i;
    //while(true){
    for(i = 0; i < 10; i++){
        cout << "> Step #" << (i + 1) << endl;
        //i++;
    }
}
