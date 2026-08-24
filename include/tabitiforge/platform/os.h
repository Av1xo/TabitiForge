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

#ifndef TABITIFORGE_PLATFORM_OS_H
#define TABITIFORGE_PLATFORM_OS_H

#include "tabitiforge/platform/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * OS MEMORY & SYSTEM INFO
 * ========================================================================= */

typedef struct tf_os_memory_info {
    tf_u64 total_physical;
    tf_u64 available_physical;
    tf_u64 page_size;
    tf_u64 allocation_granularity;
} tf_os_memory_info;

/* =========================================================================
 * VIRTUAL MEMORY API
 * ========================================================================= */

/* Reserve & Commit memory pages */
void *tf_os_memory_reserve(tf_u64 bytes);
tf_b8 tf_os_memory_commit(void *ptr, tf_u64 bytes);
void tf_os_memory_decommit(void *ptr, tf_u64 bytes);
void tf_os_memory_release(void *ptr, tf_u64 bytes);

/* =========================================================================
 * SYSTEM INFO API
 * ========================================================================= */

void tf_os_init(void);
tf_os_memory_info tf_os_get_memory_info(void);
const tf_char *tf_os_get_name(void);

#ifdef __cplusplus
}
#endif

#endif // TABITIFORGE_PLATFORM_OS_H