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

#ifndef TABITIFORGE_MEMORY_MEMORY_H
#define TABITIFORGE_MEMORY_MEMORY_H

#include "tabitiforge/platform/assert.h"
#include "tabitiforge/platform/compiler.h"
#include "tabitiforge/platform/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * ALIGNMENT HELPERS
 * ========================================================================= */

#define TF_DEFAULT_ALIGNMENT 16
#define TF_IS_POW2(x)        (((x) != 0) && (((x) & ((x) - 1)) == 0))

/**
 * Align value UP to the nearest multiple of alignment (must be power of 2).
 */
TF_FORCE_INLINE tf_u64 tf_align_up(tf_u64 value, tf_u64 alignment) {
    TF_ASSERT(TF_IS_POW2(alignment));
    return (value + (alignment - 1)) & ~(alignment - 1);
}

/**
 * Align value DOWN to the nearest multiple of alignment (must be power of 2).
 */
TF_FORCE_INLINE tf_u64 tf_align_down(tf_u64 value, tf_u64 alignment) {
    TF_ASSERT(TF_IS_POW2(alignment));
    return value & ~(alignment - 1);
}

/**
 * Calculate the padding required to align address to alignment.
 */
TF_FORCE_INLINE tf_u64 tf_align_forward_padding(tf_u64 address, tf_u64 alignment) {
    TF_ASSERT(TF_IS_POW2(alignment));
    tf_u64 modulo = address & (alignment - 1);
    if (modulo == 0)
        return 0;
    return alignment - modulo;
}

/**
 * Align pointer UP to the nearest power of 2 boundary.
 */
TF_FORCE_INLINE void *tf_align_ptr(const void *ptr, tf_u64 alignment) {
    return (void *)tf_align_up((tf_uintptr)ptr, alignment);
}

/* =========================================================================
 * MEMORY TAGS
 * ========================================================================= */
typedef enum tf_memory_tag {
    /* 0. Unassigned / System Fallback */
    TF_MEMORY_TAG_UNKNOWN = 0,

    /* 1. Core Architecture & Allocators */
    TF_MEMORY_TAG_CORE, /* Підсистеми логування, конфіги, профайлер */
    TF_MEMORY_TAG_PLATFORM, /* OS-потоки, вікна, файлова система (VFS) */
    TF_MEMORY_TAG_ARENA,    /* Самі структури Arenas / Pools / Stacks */

    /* 2. Low-Level Systems & Resources */
    TF_MEMORY_TAG_RENDERER,     /* Command buffers, Vulkan/GL state, shaders */
    TF_MEMORY_TAG_GPU_RESOURCE, /* VBO, IBO, Textures, Uniform buffers (CPU-side) */
    TF_MEMORY_TAG_ASSET,        /* Mesh data, audio clips, raw loaded files */

    /* 3. World & Simulation (ECS) */
    TF_MEMORY_TAG_SCENE,   /* Scene hierarchy, transform trees */
    TF_MEMORY_TAG_ECS,     /* Archetypes, Sparse Sets, Component arrays */
    TF_MEMORY_TAG_PHYSICS, /* Physics world, Broadphase, Rigidbodies */

    /* 4. Execution Framework */
    TF_MEMORY_TAG_JOB_SYSTEM, /* Work queues, worker thread stacks */

    TF_MEMORY_TAG_MAX_TAGS
} tf_memory_tag;

/* =========================================================================
 * MEMORY SUBSYSTEM LIFECYCLE
 * ========================================================================= */
TF_API void tf_memory_init(void);
TF_API void tf_memory_shutdown(void);

/* =========================================================================
 * TAGGED ALLOCATIONS (HEAP)
 * ========================================================================= */

TF_API void *tf_memory_alloc(tf_u64 size, tf_memory_tag tag);
TF_API void *tf_memory_alloc_aligned(tf_u64 size, tf_u64 alignment, tf_memory_tag tag);
TF_API void tf_memory_free(void *block, tf_u64 size, tf_memory_tag tag);
TF_API void tf_memory_free_aligned(void *block, tf_u64 size, tf_memory_tag tag);

/* =========================================================================
 * VIRTUAL MEMORY (DELEGATED TO OS)
 * ========================================================================= */

TF_API void *tf_memory_virtual_alloc(tf_u64 size);
TF_API void tf_memory_virtual_free(void *block, tf_u64 size);

/* =========================================================================
 * UTILITY FUNCTIONS
 * ========================================================================= */

TF_API void *tf_memory_zero(void *block, tf_u64 size);
TF_API void *tf_memory_copy(void *dest, const void *src, tf_u64 size);
TF_API void *tf_memory_set(void *dest, tf_i32 value, tf_u64 size);

#ifdef __cplusplus
}
#endif

#endif // TABITIFORGE_MEMORY_MEMORY_H