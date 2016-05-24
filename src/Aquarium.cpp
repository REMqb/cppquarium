#include "Aquarium.hpp"

#include <iostream>

using namespace std;

Aquarium::Aquarium()
{
     cout << "Initializing the aquarium" << endl << endl;
}

void Aquarium::run(){
    size_t i;
    //while(true){
    for(i = 0; i < 10; i++){
        cout << "> Step #" << (i + 1) << endl;
        //i++;
    }
}
