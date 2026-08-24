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

#include "tabitiforge/platform/os.h"
#include "tabitiforge/platform/assert.h"

#include <string.h>

/* =========================================================================
 * PLATFORM-SPECIFIC HEADERS
 * ========================================================================= */
#if TF_OS == TF_OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif TF_OS == TF_OS_LINUX
#include <sys/mman.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#endif

/* =========================================================================
 * INTERNAL STATE
 * ========================================================================= */
static tf_os_memory_info g_os_memory_info = {0};
static tf_b8 g_os_initialized = TF_FALSE;

/* =========================================================================
 * IMPLEMENTATION
 * ========================================================================= */

void tf_os_init(void) {
    if (g_os_initialized)
        return;

    memset(&g_os_memory_info, 0, sizeof(g_os_memory_info));

#if TF_OS == TF_OS_WINDOWS
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    g_os_memory_info.page_size = (tf_u64)sys_info.dwPageSize;
    g_os_memory_info.allocation_granularity = (tf_u64)sys_info.dwAllocationGranularity;
#elif TF_OS == TF_OS_LINUX
    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0)
        page_size = TF_KB(4);

    g_os_memory_info.page_size = (tf_u64)page_size;
    g_os_memory_info.allocation_granularity = (tf_u64)page_size;
#endif

    g_os_initialized = TF_TRUE;
}

tf_os_memory_info tf_os_get_memory_info(void) {
    if (!g_os_initialized) {
        tf_os_init();
    }

    tf_os_memory_info info = g_os_memory_info;

#if TF_OS == TF_OS_WINDOWS

    MEMORYSTATUSEX mem_status;
    mem_status.dwLength = sizeof(mem_status);

    if (GlobalMemoryStatusEx(&mem_status)) {
        info.total_physical = (tf_u64)mem_status.ullTotalPhys;
        info.available_physical = (tf_u64)mem_status.ullAvailPhys;
    }

#elif TF_OS == TF_OS_LINUX

    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        info.total_physical = (tf_u64)si.totalram * (tf_u64)si.mem_unit;
        info.available_physical = (tf_u64)si.freeram * (tf_u64)si.mem_unit;
    }

#endif

    return info;
}

const tf_char *tf_os_get_name(void) {
#if TF_OS == TF_OS_WINDOWS
    return "Windows";
#elif TF_OS == TF_OS_LINUX
    return "Linux";
#else
    return "Unknown";
#endif
}

/* =========================================================================
 * VIRTUAL MEMORY API IMPLEMENTATION
 * ========================================================================= */

void *tf_os_memory_reserve(tf_u64 bytes) {
    if (bytes == 0)
        return TF_NULL;
#if TF_OS == TF_OS_WINDOWS
    void *ptr = VirtualAlloc(TF_NULL, (SIZE_T)bytes, MEM_RESERVE, PAGE_NOACCESS);
    return ptr;
#elif TF_OS == TF_OS_LINUX
    void *ptr = mmap(TF_NULL, (size_t)bytes, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
        return TF_NULL;
    return ptr;
#else
    return TF_NULL;
#endif
}

tf_b8 tf_os_memory_commit(void *ptr, tf_u64 bytes) {
    if (!ptr || bytes == 0)
        return TF_FALSE;
#if TF_OS == TF_OS_WINDOWS
    void *committed_ptr = VirtualAlloc(ptr, (SIZE_T)bytes, MAM_COMMIT, PAGE_READWRITE);
    return committed_ptr != TF_NULL;
#elif TF_OS == TF_OS_LINUX
    int result = mprotect(ptr, (size_t)bytes, PROT_READ | PROT_WRITE);
    return result == 0;
#else
    return TF_FALSE;
#endif
}

void tf_os_memory_decommit(void *ptr, tf_u64 bytes) {
    if (!ptr || bytes == 0)
        return;
#if TF_OS == TF_OS_WINDOWS
    VirtualFree(ptr, (SIZE_T)bytes, MEM_DECOMMIT);
#elif TF_OS == TF_OS_LINUX
    mprotect(ptr, (size_t)bytes, PROT_NONE);
#if defined(MADV_DONTNEED)
    madvise(ptr, (size_t)bytes, MADV_DONTNEED);
#elif defined(MADV_FREE)
    madvise(ptr, (size_t)bytes, MADV_FREE);
#endif
#endif
}

void tf_os_memory_release(void *ptr, tf_u64 bytes) {
    if (!ptr)
        return;

#if TF_OS == TF_OS_WINDOWS
    (void)bytes;
    VirtualFree(ptr, 0, MEM_RELEASE);
#elif TF_OS == TF_OS_LINUX
    munmap(ptr, (size_t)bytes);
#endif
}
