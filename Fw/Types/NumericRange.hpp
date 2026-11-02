// ======================================================================
// @file   NumericRange.hpp
// @author Rob Bocchino
// @brief  Numeric range types
// ======================================================================

#ifndef FW_NUMERIC_RANGE
#define FW_NUMERIC_RANGE

#include <Fw/FPrimeBasicTypes.hpp>

// The floating-point range types depend on IEEE 754 floating point, so include
// them only if F Prime is checking for IEEE 754 compliance. See the checks in
// Fw/Types/BasicTypes.hpp.
#if !defined(SKIP_FLOAT_IEEE_754_COMPLIANCE) || !SKIP_FLOAT_IEEE_754_COMPLIANCE
#if FW_HAS_32_BIT == 1
#include <Fw/Types/F32Range.hpp>
#endif
#if FW_HAS_64_BIT == 1
#include <Fw/Types/F64Range.hpp>
#endif
#endif
#include <Fw/Types/IntRange.hpp>

#endif
