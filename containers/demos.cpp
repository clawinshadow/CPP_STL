#include "demos.h"
#include "arrays.h"
#include "vectors.h"
#include "deques.h"
#include "lists.h"
#include "forward_lists.h"
#include "common.h"

#include <iostream>

namespace containers {

void Demos()
{
    std::cout << "containers demos run \n";

    //common::Run();
    //arrays::Run();
    //vectors::Run();
    //deques::Run();
    //lists::Run();
    forward_lists::Run();
    
}

}