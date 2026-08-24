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

#ifndef TABITIFORGE_PLATFORM_CPU_H
#define TABITIFORGE_PLATFORM_CPU_H

#include "tabitiforge/platform/compiler.h"
#include "tabitiforge/platform/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * CPU FEATURE FLAGS (64-BIT BITMASK)
 * ========================================================================= */

typedef tf_u64 tf_cpu_feature;

#define TF_CPU_FEATURE_NONE 0ULL

/* x86 / x86_64 Vector & Math Extensions */
#define TF_CPU_FEATURE_SSE    (1ULL << 0)
#define TF_CPU_FEATURE_SSE2   (1ULL << 1)
#define TF_CPU_FEATURE_SSE3   (1ULL << 2)
#define TF_CPU_FEATURE_SSSE3  (1ULL << 3)
#define TF_CPU_FEATURE_SSE4_1 (1ULL << 4)
#define TF_CPU_FEATURE_SSE4_2 (1ULL << 5)
#define TF_CPU_FEATURE_AVX    (1ULL << 6)
#define TF_CPU_FEATURE_AVX2   (1ULL << 7)
#define TF_CPU_FEATURE_FMA3   (1ULL << 8)
#define TF_CPU_FEATURE_FMA4   (1ULL << 9)
#define TF_CPU_FEATURE_F16C   (1ULL << 10)

/* AVX-512 Sub-features */
#define TF_CPU_FEATURE_AVX512F         (1ULL << 11) /* Foundation */
#define TF_CPU_FEATURE_AVX512DQ        (1ULL << 12) /* Doubleword & Quadword */
#define TF_CPU_FEATURE_AVX512PF        (1ULL << 13) /* Prefetch */
#define TF_CPU_FEATURE_AVX512ER        (1ULL << 14) /* Exponential & Reciprocal */
#define TF_CPU_FEATURE_AVX512CD        (1ULL << 15) /* Conflict Detection */
#define TF_CPU_FEATURE_AVX512BW        (1ULL << 16) /* Byte & Word */
#define TF_CPU_FEATURE_AVX512VL        (1ULL << 17) /* Vector Length extensions */
#define TF_CPU_FEATURE_AVX512VBMI      (1ULL << 18)
#define TF_CPU_FEATURE_AVX512VBMI2     (1ULL << 19)
#define TF_CPU_FEATURE_AVX512VNNI      (1ULL << 20) /* Neural Network Instructions */
#define TF_CPU_FEATURE_AVX512BITALG    (1ULL << 21)
#define TF_CPU_FEATURE_AVX512VPOPCNTDQ (1ULL << 22)
#define TF_CPU_FEATURE_AVX512BF16      (1ULL << 23) /* Bfloat16 */

/* AVX10 / AMX (Modern Intel/AMD) */
#define TF_CPU_FEATURE_AVX10    (1ULL << 24)
#define TF_CPU_FEATURE_AMX_BF16 (1ULL << 25) /* Tile Matrix Multiply */
#define TF_CPU_FEATURE_AMX_TILE (1ULL << 26)
#define TF_CPU_FEATURE_AMX_INT8 (1ULL << 27)

/* x86 Bit Manipulation & System Extensions */
#define TF_CPU_FEATURE_POPCNT (1ULL << 28)
#define TF_CPU_FEATURE_BMI1   (1ULL << 29)
#define TF_CPU_FEATURE_BMI2   (1ULL << 30)
#define TF_CPU_FEATURE_LZCNT  (1ULL << 31)
#define TF_CPU_FEATURE_TZCNT  (1ULL << 32)
#define TF_CPU_FEATURE_MOVBE  (1ULL << 33)
#define TF_CPU_FEATURE_AES    (1ULL << 34)
#define TF_CPU_FEATURE_SHA    (1ULL << 35)
#define TF_CPU_FEATURE_RDRAND (1ULL << 36)
#define TF_CPU_FEATURE_RDSEED (1ULL << 37)
#define TF_CPU_FEATURE_RDTSC  (1ULL << 38)

/* ARM / ARM64 Extensions */
#define TF_CPU_FEATURE_NEON        (1ULL << 39) /* Advanced SIMD */
#define TF_CPU_FEATURE_ARM_FMA     (1ULL << 40)
#define TF_CPU_FEATURE_ARM_FP16    (1ULL << 41)
#define TF_CPU_FEATURE_SVE         (1ULL << 42) /* Scalable Vector Extension */
#define TF_CPU_FEATURE_SVE2        (1ULL << 43)
#define TF_CPU_FEATURE_SME         (1ULL << 44) /* Scalable Matrix Extension */
#define TF_CPU_FEATURE_ARM_AES     (1ULL << 45)
#define TF_CPU_FEATURE_ARM_SHA1    (1ULL << 46)
#define TF_CPU_FEATURE_ARM_SHA2    (1ULL << 47)
#define TF_CPU_FEATURE_ARM_CRC32   (1ULL << 48)
#define TF_CPU_FEATURE_ARM_ATOMICS (1ULL << 49) /* LSE Atomics */

/* =========================================================================
 * CPU CACHE TOPOLOGY
 * ========================================================================= */

typedef struct tf_cpu_cache_info {
    tf_u32 line_size;
    tf_u32 l1_data_size; /* L1 Data */
    tf_u32 l1_inst_size; /* L1 Instruction */
    tf_u32 l2_size;      /* L2 cache */
    tf_u32 l3_size;      /* L3 (Shared) */
} tf_cpu_cache_info;

/* =========================================================================
 * CPU TOPOLOGY & NUMA
 * ========================================================================= */

typedef struct tf_cpu_topology {
    tf_u32 logical_cores;
    tf_u32 physical_cores;
    tf_u32 performance_cores; /* P-Cores (for x86 hybrid / Apple Silicon) */
    tf_u32 efficiency_cores;  /* E-Cores */
    tf_u32 sockets;           /* phys socket / CPU */
    tf_u32 numa_nodes;        /* NUMA-nodes */
} tf_cpu_topology;

/* =========================================================================
 * FULL CPU INFO STRUCTURE
 * ========================================================================= */

typedef struct tf_cpu_info {
    tf_u64 features_mask;
    tf_cpu_topology topology;
    tf_cpu_cache_info cache;
    tf_u32 simd_alignment;  /* Recommended_alignment (16/32/64B) */
    char vendor_string[13]; /* vendor */
    char brand_string[49];  /* brand name */
} tf_cpu_info;

/* =========================================================================
 * RUNTIME CPU DETECTION API
 * ========================================================================= */

void tf_cpu_init(void);

const tf_cpu_info *tf_cpu_get_info(void);

TF_FORCE_INLINE tf_b8 tf_cpu_has_feature(tf_cpu_feature feature) {
    const tf_cpu_info *info = tf_cpu_get_info();
    return (info->features_mask & feature) == feature;
}

#ifdef __cplusplus
}
#endif

#endif