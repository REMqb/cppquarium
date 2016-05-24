#include <iostream>

#include "Aquarium.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "==================" << endl
         << "== Cppquarium   ==" << endl
         << "==================" << endl << endl;

    Aquarium aquarium;

    aquarium.run();

    return 0;
}
