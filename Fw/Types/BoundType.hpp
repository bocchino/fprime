// ======================================================================
// @file   BoundType.hpp
// @author Rob Bocchino
// @brief  The type of a bound
// ======================================================================

#ifndef FW_BOUND_TYPE
#define FW_BOUND_TYPE

#include <Fw/FPrimeBasicTypes.hpp>

namespace Fw {

//! The type of a bound
enum class BoundType {
    NONE,       //!< No bound
    INCLUSIVE,  //!< An inclusive bound
    EXCLUSIVE   //!< An exclusive bound
};

}

#endif
