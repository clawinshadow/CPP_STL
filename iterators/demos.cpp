#include "demos.h"
#include "categories.h"
#include "auxiliary.h"
#include "adapters.h"

#include <iostream>

namespace iterators {

void Run()
{
    std::cout << "Iterators demos Run.." << std::endl;
    //categories::Demo();
    //auxiliary::Demo();
    adapters::Demos();
}

}