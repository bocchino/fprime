// ======================================================================
// @file   NumericRange.hpp
// @author Rob Bocchino
// @brief  Numeric range types
// ======================================================================

#ifndef FW_NUMERIC_RANGE
#define FW_NUMERIC_RANGE

#include <Fw/FPrimeBasicTypes.hpp>

// The floating-point range types depend on IEEE 754 floating point, so they are
// available only if F Prime is checking for IEEE 754 compliance. See the checks
// in Fw/Types/BasicTypes.hpp. FW_HAS_F32_RANGE and FW_HAS_F64_RANGE record
// whether each type is available. Use them to guard code that uses the type.
#if (!defined(SKIP_FLOAT_IEEE_754_COMPLIANCE) || !SKIP_FLOAT_IEEE_754_COMPLIANCE) && (FW_HAS_32_BIT == 1)
#define FW_HAS_F32_RANGE 1
#else
#define FW_HAS_F32_RANGE 0
#endif
#if (!defined(SKIP_FLOAT_IEEE_754_COMPLIANCE) || !SKIP_FLOAT_IEEE_754_COMPLIANCE) && (FW_HAS_64_BIT == 1)
#define FW_HAS_F64_RANGE 1
#else
#define FW_HAS_F64_RANGE 0
#endif

#if FW_HAS_F32_RANGE
#include <Fw/Types/F32Range.hpp>
#endif
#if FW_HAS_F64_RANGE
#include <Fw/Types/F64Range.hpp>
#endif
#include <Fw/Types/IntRange.hpp>

#endif
