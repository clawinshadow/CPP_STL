#include "demos.h"
#include "arrays.h"
#include "vectors.h"
#include "deques.h"
#include "lists.h"
#include "forward_lists.h"
#include "common.h"
#include "sets.h"
#include "maps.h"
#include "others.h"

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
    //forward_lists::Run();
    //sets::Run();
    //maps::Run();
    //maps::RunEx();
    //others::StringsDemo();
    //others::C_Arrays_Demo();
    others::Reference_Semantics();
    others::Reference_Wrapper();
}

}