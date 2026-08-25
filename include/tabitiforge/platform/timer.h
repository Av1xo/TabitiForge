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

#ifndef TABITIFORGE_PLATFORM_TIMER_H
#define TABITIFORGE_PLATFORM_TIMER_H

#include "tabitiforge/platform/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * HIGH-RESOLUTION TIMER
 * ========================================================================= */

typedef struct tf_timer {
    tf_u64 start_ticks;
} tf_timer;

void tf_timer_init(void);
tf_u64 tf_timer_get_ticks(void);
tf_u64 tf_timer_get_frequency(void);
tf_f64 tf_timer_get_time_seconds(void);

/* =========================================================================
 * STOPWATCH / PROFILING API
 * ========================================================================= */

tf_timer tf_timer_start(void);

tf_f64 tf_timer_elapsed_seconds(const tf_timer *timer);
tf_f64 tf_timer_elapsed_milliseconds(const tf_timer *timer);
tf_f64 tf_timer_restart(tf_timer *timer);

void tf_timer_sleep(tf_u32 ms);

#ifdef __cplusplus
}
#endif

#endif // TABITIFORGE_PLATFORM_TIMER_H