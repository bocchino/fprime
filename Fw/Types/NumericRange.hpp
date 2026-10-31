// ======================================================================
// @file   NumericRange.hpp
// @author Rob Bocchino
// @brief  Numeric range types
// ======================================================================

#ifndef FW_NUMERIC_RANGE
#define FW_NUMERIC_RANGE

#if FW_HAS_32_BIT == 1
#include <Fw/Types/F32Range.hpp>
#endif
#if FW_HAS_64_BIT == 1
#include <Fw/Types/F64Range.hpp>
#endif
#include <Fw/Types/IntRange.hpp>

#endif
