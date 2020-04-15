#include "demos.h"
#include "basics.h"
#include "binders.h"
#include "lambdas.h"

#include <iostream>

namespace function_objects {

void Demos()
{
    std::cout << "function objects demos" << std::endl;

    //basics::Run();
    //binders::Run();
    lambdas::Run();
}

}