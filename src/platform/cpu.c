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

#include "tabitiforge/platform/cpu.h"
#include "tabitiforge/platform/assert.h"

#include <string.h>

/* =========================================================================
 * ARCHITECTURE DEPENDENT INCLUDES & HELPERS
 * ========================================================================= */

#if TF_ARCH == TF_ARCH_X86 || TF_ARCH == TF_ARCH_X64

#if TF_COMPILER == TF_COMPILER_MSVC
#include <intrin.h>
#else
#include <cpuid.h>
#endif

static void tf_internal_cpuid(tf_i32 leaf, tf_i32 subleaf, tf_u32 regs[4]) {
#if TF_COMPILER == TF_COMPILER_MSVC
    __cpuidex((int *)regs, leaf, subleaf);
#else
    __cpuid_count(leaf, subleaf, regs[0], regs[1], regs[2], regs[3]);
#endif
}

static tf_u64 tf_internal_xgetbv(tf_u32 xcr) {
#if TF_COMPILER == TF_COMPILER_MSVC
    return _xgetbv(xcr);
#else
    tf_u32 eax;
    tf_u32 edx;

    __asm__ volatile("xgetbv" : "=a"(eax), "=d"(edx) : "c"(xcr));

    return ((tf_u64)edx << 32) | eax;
#endif
}

#elif TF_ARCH == TF_ARCH_ARM32 || TF_ARCH == TF_ARCH_ARM64

#if TF_OS == TF_OS_LINUX

#include <sys/auxv.h>

#if TF_ARCH == TF_ARCH_ARM64
#include <asm/hwcap.h>
#elif TF_ARCH == TF_ARCH_ARM32
#include <asm/hwcap.h>
#endif

#elif TF_OS == TF_OS_WINDOWS

#if TF_ARCH == TF_ARCH_ARM64
#include <windows.h>
#endif

#endif

#endif

/* =========================================================================
 * INTERNAL STATE
 * ========================================================================= */

static tf_cpu_info g_cpu_info = {0};
static tf_b8 g_cpu_initialized = TF_FALSE;

/* =========================================================================
 * IMPLEMENTATION
 * ========================================================================= */

void tf_cpu_init(void) {
    if (g_cpu_initialized) {
        return;
    }

    memset(&g_cpu_info, 0, sizeof(g_cpu_info));

    /*
     * Safe baseline values.
     *
     * These values are deliberately conservative and are replaced
     * with runtime-detected values where available.
     */
    g_cpu_info.cache.line_size = 64;

    g_cpu_info.topology.logical_cores = 1;
    g_cpu_info.topology.physical_cores = 1;
    g_cpu_info.topology.sockets = 1;
    g_cpu_info.topology.numa_nodes = 1;

    g_cpu_info.simd_alignment = 16;

    /* =========================================================================
     * x86 / x86_64
     * ========================================================================= */

#if TF_ARCH == TF_ARCH_X86 || TF_ARCH == TF_ARCH_X64

    tf_u32 regs[4] = {0};

    /*
     * CPUID leaf 0:
     *
     * EAX = highest supported basic CPUID leaf
     * EBX/EDX/ECX = vendor string
     */
    tf_internal_cpuid(0, 0, regs);

    tf_u32 max_leaf = regs[0];

    tf_u32 *vendor_ptr = (tf_u32 *)g_cpu_info.vendor_string;

    vendor_ptr[0] = regs[1]; /* EBX */
    vendor_ptr[1] = regs[3]; /* EDX */
    vendor_ptr[2] = regs[2]; /* ECX */

    g_cpu_info.vendor_string[12] = '\0';

    /*
     * Extended CPUID leaves.
     *
     * 0x80000000 -> highest supported extended leaf
     */
    tf_internal_cpuid((tf_i32)0x80000000, 0, regs);

    tf_u32 max_ext_leaf = regs[0];

    /*
     * Brand string occupies leaves:
     *
     * 0x80000002
     * 0x80000003
     * 0x80000004
     */
    if (max_ext_leaf >= 0x80000004) {
        tf_u32 *brand_ptr = (tf_u32 *)g_cpu_info.brand_string;

        tf_internal_cpuid((tf_i32)0x80000002, 0, &brand_ptr[0]);
        tf_internal_cpuid((tf_i32)0x80000003, 0, &brand_ptr[4]);
        tf_internal_cpuid((tf_i32)0x80000004, 0, &brand_ptr[8]);

        g_cpu_info.brand_string[48] = '\0';
    }

    /* =========================================================================
     * CPUID LEAF 1
     * ========================================================================= */

    if (max_leaf >= 1) {
        tf_internal_cpuid(1, 0, regs);

        tf_u32 ecx = regs[2];
        tf_u32 edx = regs[3];

        /*
         * EDX features.
         */

        if (edx & (1u << 25)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_SSE;
        }

        if (edx & (1u << 26)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_SSE2;
        }

        /*
         * ECX features.
         */

        if (ecx & (1u << 0)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_SSE3;
        }

        if (ecx & (1u << 9)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_SSSE3;
        }

        if (ecx & (1u << 19)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_SSE4_1;
        }

        if (ecx & (1u << 20)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_SSE4_2;
        }

        if (ecx & (1u << 23)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_POPCNT;
        }

        if (ecx & (1u << 25)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_AES;
        }

        if (ecx & (1u << 29)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_F16C;
        }

        if (ecx & (1u << 12)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_FMA3;
        }

        if (ecx & (1u << 30)) {
            g_cpu_info.features_mask |= TF_CPU_FEATURE_RDRAND;
        }

        /*
         * AVX requires:
         *
         * CPU supports AVX
         * CPU supports XSAVE
         * OS supports XSAVE/XMM/YMM state management
         */
        tf_b8 osxsave = (ecx & (1u << 27)) != 0;

        tf_b8 avx_supported = (ecx & (1u << 28)) != 0;

        if (osxsave && avx_supported) {

            tf_u64 xcr0 = tf_internal_xgetbv(0);

            /*
             * XCR0:
             *
             * bit 1 = XMM state
             * bit 2 = YMM state
             */
            if ((xcr0 & 0x6u) == 0x6u) {

                g_cpu_info.features_mask |= TF_CPU_FEATURE_AVX;
                g_cpu_info.simd_alignment = 32;

                /* =========================================================================
                 * CPUID LEAF 7
                 * ========================================================================= */

                if (max_leaf >= 7) {

                    tf_u32 leaf7[4] = {0};

                    tf_internal_cpuid(7, 0, leaf7);

                    tf_u32 ebx7 = leaf7[1];
                    tf_u32 ecx7 = leaf7[2];

                    /*
                     * EBX
                     */

                    if (ebx7 & (1u << 5)) {
                        g_cpu_info.features_mask |= TF_CPU_FEATURE_AVX2;
                    }

                    if (ebx7 & (1u << 3)) {
                        g_cpu_info.features_mask |= TF_CPU_FEATURE_BMI1;
                    }

                    if (ebx7 & (1u << 8)) {
                        g_cpu_info.features_mask |= TF_CPU_FEATURE_BMI2;
                    }

                    if (ebx7 & (1u << 29)) {
                        g_cpu_info.features_mask |= TF_CPU_FEATURE_SHA;
                    }

                    if (ebx7 & (1u << 18)) {
                        g_cpu_info.features_mask |= TF_CPU_FEATURE_RDSEED;
                    }

                    /*
                     * AVX-512 requires OS support for:
                     *
                     * XMM   bit 1
                     * YMM   bit 2
                     * Opmask bit 5
                     * ZMM_Hi256 bit 6
                     * Hi16_ZMM bit 7
                     */
                    if ((xcr0 & 0xE6u) == 0xE6u) {

                        if (ebx7 & (1u << 16)) {
                            g_cpu_info.features_mask |= TF_CPU_FEATURE_AVX512F;

                            g_cpu_info.simd_alignment = 64;
                        }

                        if (ebx7 & (1u << 17)) {
                            g_cpu_info.features_mask |= TF_CPU_FEATURE_AVX512DQ;
                        }

                        if (ebx7 & (1u << 28)) {
                            g_cpu_info.features_mask |= TF_CPU_FEATURE_AVX512CD;
                        }

                        if (ebx7 & (1u << 30)) {
                            g_cpu_info.features_mask |= TF_CPU_FEATURE_AVX512BW;
                        }

                        if (ebx7 & (1u << 31)) {
                            g_cpu_info.features_mask |= TF_CPU_FEATURE_AVX512VL;
                        }

                        if (ecx7 & (1u << 1)) {
                            g_cpu_info.features_mask |= TF_CPU_FEATURE_AVX512VBMI;
                        }

                        if (ecx7 & (1u << 11)) {
                            g_cpu_info.features_mask |= TF_CPU_FEATURE_AVX512VNNI;
                        }
                    }
                }
            }
        }
    }

    /* =========================================================================
     * ARM / ARM64
     * ========================================================================= */

#elif TF_ARCH == TF_ARCH_ARM32 || TF_ARCH == TF_ARCH_ARM64

#if TF_ARCH == TF_ARCH_ARM64

    /*
     * ARMv8-A / ARM64 guarantees Advanced SIMD (NEON)
     * and floating-point support.
     */
    g_cpu_info.features_mask |= TF_CPU_FEATURE_NEON;
    g_cpu_info.features_mask |= TF_CPU_FEATURE_ARM_FMA;

    g_cpu_info.simd_alignment = 16;

    strncpy(g_cpu_info.vendor_string, "ARM", sizeof(g_cpu_info.vendor_string) - 1);

#endif

#if TF_OS == TF_OS_LINUX

    tf_u64 hwcap = getauxval(AT_HWCAP);

#if defined(HWCAP_SVE)

    if (hwcap & HWCAP_SVE) {
        g_cpu_info.features_mask |= TF_CPU_FEATURE_SVE;
    }

#endif

#if defined(HWCAP_AES)

    if (hwcap & HWCAP_AES) {
        g_cpu_info.features_mask |= TF_CPU_FEATURE_ARM_AES;
    }

#endif

#if defined(HWCAP_SHA1)

    if (hwcap & HWCAP_SHA1) {
        g_cpu_info.features_mask |= TF_CPU_FEATURE_ARM_SHA1;
    }

#endif

#if defined(HWCAP_SHA2)

    if (hwcap & HWCAP_SHA2) {
        g_cpu_info.features_mask |= TF_CPU_FEATURE_ARM_SHA2;
    }

#endif

#if defined(HWCAP_CRC32)

    if (hwcap & HWCAP_CRC32) {
        g_cpu_info.features_mask |= TF_CPU_FEATURE_ARM_CRC32;
    }

#endif

#endif /* TF_OS == TF_OS_LINUX */

#endif /* architecture */

    /* =========================================================================
     * FINALIZE
     * ========================================================================= */

    g_cpu_initialized = TF_TRUE;
}

/* =========================================================================
 * PUBLIC API
 * ========================================================================= */

const tf_cpu_info *tf_cpu_get_info(void) {
    if (!g_cpu_initialized) {
        tf_cpu_init();
    }

    return &g_cpu_info;
}