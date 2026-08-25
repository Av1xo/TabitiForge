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

#include "tabitiforge/memory/memory.h"
#include "tabitiforge/platform/os.h"

#include <stdlib.h>
#include <string.h>

typedef struct tf_memory_stats {
    tf_u64 total_allocated;
    tf_u64 tagged_allocations[TF_MEMORY_TAG_MAX_TAGS];
} tf_memory_stats;

static tf_memory_stats g_memory_stats = {0};
static tf_b8 g_memory_initialized = TF_FALSE;

void tf_memory_init(void) {
    if (g_memory_initialized)
        return;

    tf_os_init();
    memset(&g_memory_stats, 0, sizeof(tf_memory_stats));
    g_memory_initialized = TF_TRUE;
}

void tf_memory_shutdown(void) {
    if (!g_memory_initialized)
        return;
    if (g_memory_stats.total_allocated > 0) {
        TF_ASSERT_MSG(TF_FALSE, "Memory leak detected during shutdown!");
    }

    g_memory_initialized = TF_FALSE;
}

void *tf_memory_virtual_alloc(tf_u64 size) {
    void *ptr = tf_os_memory_reserve(size);
    if (ptr) {
        if (!tf_os_memory_commit(ptr, size)) {
            tf_os_memory_release(ptr, size);
            return TF_NULL;
        }
    }
    return ptr;
}

void tf_memory_virtual_free(void *block, tf_u64 size) {
    if (!block)
        return;
    tf_os_memory_decommit(block, size);
    tf_os_memory_release(block, size);
}

void *tf_memory_alloc(tf_u64 size, tf_memory_tag tag) {
    TF_ASSERT_MSG(tag != TF_MEMORY_TAG_UNKNOWN,
                  "Cannot allocate memory with TF_MEMORY_TAG_UNKNOWN");
    if (!g_memory_initialized)
        tf_memory_init();

    void *block = malloc((tf_size)size);
    if (block) {
        memset(block, 0, (tf_size)size);
        g_memory_stats.total_allocated += size;
        g_memory_stats.tagged_allocations[tag] += size;
    }
    return block;
}

void *tf_memory_alloc_aligned(tf_u64 size, tf_u64 alignment, tf_memory_tag tag) {
    if (size == 0)
        return TF_NULL;
    TF_ASSERT_MSG(TF_IS_POW2(alignment), "Alignment must be a power of 2");
    if (!g_memory_initialized)
        tf_memory_init();

    void *ptr = TF_NULL;

#if TF_OS == TF_OS_WINDOWS
    ptr = _aligned_malloc((tf_size)size, (tf_size)alignment);
#elif TF_OS == TF_OS_LINUX
    if (posix_memalign(&ptr, (tf_size)alignment, (tf_size)size) != 0) {
        ptr = TF_NULL;
    }
#endif

    if (ptr) {
        memset(ptr, 0, (tf_size)size);
        g_memory_stats.total_allocated += size;
        g_memory_stats.tagged_allocations[tag] += size;
    }

    return ptr;
}

void tf_memory_free(void *block, tf_u64 size, tf_memory_tag tag) {
    if (!block)
        return;
    TF_ASSERT_MSG(tag != TF_MEMORY_TAG_UNKNOWN, "Cannot free memory with TF_MEMORY_TAG_UNKNOWN");

    g_memory_stats.total_allocated -= size;
    g_memory_stats.tagged_allocations[tag] -= size;
    free(block);
}

void tf_memory_free_aligned(void *block, tf_u64 size, tf_memory_tag tag) {
    if (!block)
        return;

    g_memory_stats.total_allocated -= size;
    g_memory_stats.tagged_allocations[tag] -= size;

#if TF_OS == TF_OS_WINDOWS
    _aligned_free(block);
#elif TF_OS == TF_OS_LINUX
    free(block);
#endif
}

void *tf_memory_zero(void *block, tf_u64 size) {
    return memset(block, 0, (size_t)size);
}
void *tf_memory_copy(void *dest, const void *src, tf_u64 size) {
    return memcpy(dest, src, (size_t)size);
}
void *tf_memory_set(void *dest, tf_i32 value, tf_u64 size) {
    return memset(dest, value, (size_t)size);
}
