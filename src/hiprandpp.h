//------------------------------------------------------------------------------
/// \file
/// \brief      C++ wrappers for the hipRAND routines used in CoralGemm
/// \date       2020-2021
/// \author     Jakub Kurzak
/// \copyright  Advanced Micro Devices, Inc.
///
#pragma once

#include "Exception.h"

#if defined(__HIPCC__) || defined(__HIP_PLATFORM__)
#include <hiprand.h>
#endif

#if defined(__NVCC__)
#include <curand.h>
#endif

/// C++ wrappers for hipRAND
namespace hiprand {

/// Generate uniform (float).
inline
void generateUniform(
    hiprandGenerator_t generator, float* A, std::size_t len)
{
    HIPRAND_CALL(hiprandGenerateUniform(generator, A, len));
}

/// Generate uniform (double).
inline
void generateUniform(
    hiprandGenerator_t generator, double* A, std::size_t len)
{
    HIPRAND_CALL(hiprandGenerateUniformDouble(generator, A, len));
}

/// Generate uniform (complex<float>).
inline
void generateUniform(
    hiprandGenerator_t generator, std::complex<float>* A, std::size_t len)
{
    HIPRAND_CALL(hiprandGenerateUniform(generator, (float*)A, len*2));
}

/// Generate uniform (complex<double>).
inline
void generateUniform(
    hiprandGenerator_t generator, std::complex<double>* A, std::size_t len)
{
    HIPRAND_CALL(hiprandGenerateUniformDouble(generator, (double*)A, len*2));
}

/// Generate uniform (int8_t).
/// \remark Silly implementation generating len/4 of int32_t.
/// \todo Replace with hiprandGenerateChar() when available.
inline
void generateUniform(
    hiprandGenerator_t generator, int8_t* A, std::size_t len)
{
#if defined(__NVCC__) && !defined(__HIP_PLATFORM__)
    ASSERT(len%4 == 0);
    HIPRAND_CALL(hiprandGenerate(generator, (unsigned int*)A, len/4));
#else
    HIPRAND_CALL(hiprandGenerateChar(generator, (unsigned char*)A, len));
#endif
}

/// Generate uniform (int32_t).
inline
void generateUniform(
    hiprandGenerator_t generator, int32_t* A, std::size_t len)
{
    HIPRAND_CALL(hiprandGenerate(generator, (unsigned int*)A, len));
}

} // namespace hiprand