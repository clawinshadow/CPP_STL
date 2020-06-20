#include "utility_demos.h"
#include "pairs_and_tuples.h"
#include "smart_pointers.h"
#include "type_trait.h"
#include "auxiliary_functions.h"

namespace utility {
namespace demos {

void Run()
{
    // pairs_tuples::pairs_demo();
    // pairs_tuples::tuple_demo();
    // smart_pointers::shared_ptr_demo();
    // smart_pointers::weak_ptr_demo();
     smart_pointers::shared_ptr_missuse_demo();
    // smart_pointers::unique_ptr_demo();
    // type_trait::basic_demo();
    // type_trait::wrappers_demo();
    // auxiliary_funcs::minmax_demo();
//    auxiliary_funcs::swap_demo();
//    auxiliary_funcs::ratio_demo();
    // auxiliary_funcs::durations_demo();
//    auxiliary_funcs::clock_demo();
//    auxiliary_funcs::timepoint_demo();
//    auxiliary_funcs::ctime_demo();
}

} //namespace demos
} //namespace utility