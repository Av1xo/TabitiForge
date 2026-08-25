/*
 * Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
 * TabitiForge Simulation Engine
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TABITIFORGE_PLATFORM_COMPILER_H
#define TABITIFORGE_PLATFORM_COMPILER_H

/* =========================================================================
 * OS DETECTION
 * ========================================================================= */
#define TF_OS_WINDOWS 1
#define TF_OS_LINUX   2

#if defined(_WIN32) || defined(_WIN64)
#define TF_OS TF_OS_WINDOWS
#elif defined(__linux__)
#define TF_OS TF_OS_LINUX
#else
#error "Unsupported Operating System! TabitiForge supports Windows and Linux."
#endif

/* =========================================================================
 * COMPILER DETECTION
 * ========================================================================= */
#define TF_COMPILER_CLANG 1
#define TF_COMPILER_GCC   2
#define TF_COMPILER_MSVC  3

#if defined(__clang__)
#define TF_COMPILER TF_COMPILER_CLANG
#elif defined(_MSC_VER)
#define TF_COMPILER TF_COMPILER_MSVC
#elif defined(__GNUC__)
#define TF_COMPILER TF_COMPILER_GCC
#else
#error "Unsupported Compiler!"
#endif

/* =========================================================================
 * ARCHITECTURE DETECTION
 * ========================================================================= */
#define TF_ARCH_X86   1
#define TF_ARCH_X64   2
#define TF_ARCH_ARM32 3
#define TF_ARCH_ARM64 4

#if defined(__x86_64__) || defined(_M_X64)
#define TF_ARCH TF_ARCH_X64
#elif defined(__i386__) || defined(_M_IX86)
#define TF_ARCH TF_ARCH_X86
#elif defined(__aarch64__) || defined(_M_ARM64)
#define TF_ARCH TF_ARCH_ARM64
#elif defined(__arm__) || defined(_M_ARM)
#define TF_ARCH TF_ARCH_ARM32
#else
#error "Unsupported Architecture!"
#endif

/* =========================================================================
 * POINTER SIZE DETECTION
 * ========================================================================= */
#define TF_PTR_BITS_32 32
#define TF_PTR_BITS_64 64

#if defined(__SIZEOF_POINTER__)
#if __SIZEOF_POINTER__ == 8
#define TF_PTR_BITS TF_PTR_BITS_64
#elif __SIZEOF_POINTER__ == 4
#define TF_PTR_BITS TF_PTR_BITS_32
#else
#error "Unsupported pointer width!"
#endif
#elif defined(_WIN64) || defined(__LP64__) || defined(_LP64)
#define TF_PTR_BITS TF_PTR_BITS_64
#elif defined(_WIN32)
#define TF_PTR_BITS TF_PTR_BITS_32
#else
#error "Unable to determine pointer width!"
#endif

/* =========================================================================
 * BUILD CONFIGURATION DETECTION
 * ========================================================================= */
#define TF_RELEASE 1
#define TF_DEBUG   2

#if defined(NDEBUG) || defined(_NDEBUG)
#define TF_BUILD TF_RELEASE
#else
#define TF_BUILD TF_DEBUG
#endif

/* =========================================================================
 * ENDIANNESS DETECTION
 * ========================================================================= */
#define TF_ENDIAN_LITTLE 1
#define TF_ENDIAN_BIG    2

#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define TF_ENDIAN TF_ENDIAN_BIG
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define TF_ENDIAN TF_ENDIAN_LITTLE
#else
#error "Unsupported byte order!"
#endif
#elif defined(__BIG_ENDIAN__) || defined(_BIG_ENDIAN)
#define TF_ENDIAN TF_ENDIAN_BIG
#elif defined(__LITTLE_ENDIAN__) || defined(_LITTLE_ENDIAN)
#define TF_ENDIAN TF_ENDIAN_LITTLE
#elif defined(_WIN32)
/*
 * Windows targets supported by TabitiForge are little-endian.
 */
#define TF_ENDIAN TF_ENDIAN_LITTLE
#else
#error "Unable to determine endianness!"
#endif

/* =========================================================================
 * SIMD / VECTOR EXTENSION DETECTION
 * ========================================================================= */
#if defined(__AVX512F__)
#define TF_SIMD_AVX512 1
#define TF_SIMD_LEVEL  5
#elif defined(__AVX2__)
#define TF_SIMD_AVX2  1
#define TF_SIMD_LEVEL 4
#elif defined(__AVX__)
#define TF_SIMD_AVX   1
#define TF_SIMD_LEVEL 3
#elif defined(__SSE4_2__)
#define TF_SIMD_SSE4_2 1
#define TF_SIMD_LEVEL  2
#elif defined(__SSE4_1__) || defined(__SSE3__) || defined(__SSE2__) || defined(_M_AMD64) ||        \
    defined(_M_X64)
#define TF_SIMD_SSE2  1
#define TF_SIMD_LEVEL 1
#elif defined(__ARM_NEON) || defined(__ARM_NEON__) || defined(_M_ARM64) || defined(_M_ARM)
#define TF_SIMD_NEON  1
#define TF_SIMD_LEVEL 1
#else
#define TF_SIMD_NONE  1
#define TF_SIMD_LEVEL 0
#endif

/* =========================================================================
 * SIMD ALIGNMENT
 * ========================================================================= */
#if TF_SIMD_LEVEL >= 5
#define TF_SIMD_ALIGNMENT 64
#elif TF_SIMD_LEVEL >= 3 /* AVX / AVX2 */
#define TF_SIMD_ALIGNMENT 32
#elif TF_SIMD_LEVEL >= 1 /* SSE / NEON */
#define TF_SIMD_ALIGNMENT 16
#else
#define TF_SIMD_ALIGNMENT 8
#endif

/* =========================================================================
 * ATTRIBUTES & INLINING
 * ========================================================================= */
#if TF_COMPILER == TF_COMPILER_MSVC
#define TF_FORCE_INLINE __forceinline
#define TF_NEVER_INLINE __declspec(noinline)
#define TF_ALIGN(bytes) __declspec(align(bytes))
#define TF_RESTRICT     __restrict
#elif TF_COMPILER == TF_COMPILER_GCC || TF_COMPILER == TF_COMPILER_CLANG
#define TF_FORCE_INLINE inline __attribute__((always_inline))
#define TF_NEVER_INLINE __attribute__((noinline))
#define TF_ALIGN(bytes) __attribute__((aligned(bytes)))
#define TF_RESTRICT     __restrict__
#else
#define TF_FORCE_INLINE inline
#define TF_NEVER_INLINE
#define TF_ALIGN(bytes)
#define TF_RESTRICT
#endif

#define TF_SIMD_ALIGNED TF_ALIGN(TF_SIMD_ALIGNMENT)

/* =========================================================================
 * DEBUG BREAK
 * ========================================================================= */
#if TF_BUILD == TF_DEBUG
#if TF_COMPILER == TF_COMPILER_MSVC
#define TF_DEBUG_BREAK() __debugbreak()
#elif TF_ARCH == TF_ARCH_X64 || TF_ARCH == TF_ARCH_X86
#if TF_COMPILER == TF_COMPILER_GCC || TF_COMPILER == TF_COMPILER_CLANG
#define TF_DEBUG_BREAK() __asm__ volatile("int $3")
#else
#include <signal.h>
#define TF_DEBUG_BREAK() raise(SIGTRAP)
#endif
#elif TF_ARCH == TF_ARCH_ARM64
#if TF_COMPILER == TF_COMPILER_GCC || TF_COMPILER == TF_COMPILER_CLANG
#define TF_DEBUG_BREAK() __asm__ volatile("brk #0xf000")
#else
#define TF_DEBUG_BREAK() __builtin_trap()
#endif
#elif TF_ARCH == TF_ARCH_ARM32
#define TF_DEBUG_BREAK() __builtin_trap()
#else
#include <signal.h>
#define TF_DEBUG_BREAK() raise(SIGTRAP)
#endif
#else
#define TF_DEBUG_BREAK() ((void)0)
#endif

/* =========================================================================
 * BRANCH PREDICTION & UNREACHABLE
 * ========================================================================= */
#if TF_COMPILER == TF_COMPILER_GCC || TF_COMPILER == TF_COMPILER_CLANG
#define TF_LIKELY(x)     __builtin_expect(!!(x), 1)
#define TF_UNLIKELY(x)   __builtin_expect(!!(x), 0)
#define TF_UNREACHABLE() __builtin_unreachable()
#elif TF_COMPILER == TF_COMPILER_MSVC
#define TF_LIKELY(x)     (x)
#define TF_UNLIKELY(x)   (x)
#define TF_UNREACHABLE() __assume(0)
#else
#define TF_LIKELY(x)     (x)
#define TF_UNLIKELY(x)   (x)
#define TF_UNREACHABLE() ((void)0)
#endif

/* =========================================================================
 * API EXPORT / IMPORT
 * ========================================================================= */
#if TF_OS == TF_OS_WINDOWS
#if TF_COMPILER == TF_COMPILER_MSVC || defined(__declspec)
#define TF_API_EXPORT __declspec(dllexport)
#define TF_API_IMPORT __declspec(dllimport)
#else
#define TF_API_EXPORT
#define TF_API_IMPORT
#endif
#else
#if TF_COMPILER == TF_COMPILER_GCC || TF_COMPILER == TF_COMPILER_CLANG
#define TF_API_EXPORT __attribute__((visibility("default")))
#define TF_API_IMPORT
#else
#define TF_API_EXPORT
#define TF_API_IMPORT
#endif
#endif

#if defined(TF_SHARED_LIB)
#if defined(TF_EXPORT_SYMBOLS)
#define TF_API TF_API_EXPORT
#else
#define TF_API TF_API_IMPORT
#endif
#else
#define TF_API
#endif

/* =========================================================================
 * C STANDARD LEVEL DETECTION
 * ========================================================================= */
#if defined(__STDC_VERSION__)
#define TF_C_VERSION __STDC_VERSION__
#else
#define TF_C_VERSION 0L
#endif

#define TF_C99_OR_GREATER (TF_C_VERSION >= 199901L)
#define TF_C11_OR_GREATER (TF_C_VERSION >= 201112L)

#endif /* TABITIFORGE_PLATFORM_COMPILER_H */