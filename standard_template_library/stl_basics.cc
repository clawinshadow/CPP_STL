#include "stl_basics.h"
#include "containers.h"
#include "iterators.h"
#include "algorithms.h"
#include "func_arguments.h"

namespace stl_basics {

// standard  template library (STL): three components
//     1. Containers
//     2. Iterators
//     3. Algorithms
void Run()
{
    //containers::SequenceContainersDemo();
    //containers::AssociateContainersDemo();
    //containers::UnorderedContainersDemo();
    //iterators::Demo();
    //iterators::IteratorAdaptersDemo();
    //algorithms::Demo();
    //algorithms::RangeDemo();
    //algorithms::RemovingDemo();
    func_arguments::Demo();
    func_arguments::PredicatesDemo();
}

}