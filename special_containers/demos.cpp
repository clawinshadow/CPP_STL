#include "demos.h"
#include "stacks.h"

#include <iostream>

using namespace std;

namespace special_containers {

    /*
     *  The C++ standard library provides not only the containers for the STL framework but also some
        containers that fit some special needs and provide simple, almost self-explanatory, interfaces. You
        can group these containers into either the so-called container adapters, which adapt standard STL
        containers to fit special needs, or a bitset, which is a containers for bits or Boolean values.

        There are three standard container adapters: stacks, queues, and priority queues.
     */

void Demos()
{
    cout << "Special containers demos.. " << endl;

    stacks::Run();
}

}