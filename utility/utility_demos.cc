#include "utility_demos.h"
#include "pairs_and_tuples.h"
#include "smart_pointers.h"

namespace utility {
namespace demos {

void Run()
{
    // pairs_tuples::pairs_demo();
    // pairs_tuples::tuple_demo();
    // smart_pointers::shared_ptr_demo();
    // smart_pointers::weak_ptr_demo();
    // smart_pointers::shared_ptr_missuse_demo();
    smart_pointers::unique_ptr_demo();
}

} //namespace demos
} //namespace utility