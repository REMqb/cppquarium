#include <iostream>

#include "Aquarium.hpp"

using namespace std;

int main(int argc, char *argv[]){
    cout << "==================" << endl
         << "== Cppquarium   ==" << endl
         << "==================" << endl << endl;

    Aquarium aquarium;

    aquarium.populate();
    aquarium.run();

    return 0;
}
