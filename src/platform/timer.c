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

#if !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 199309L
#endif

#include "tabitiforge/platform/timer.h"
#include "tabitiforge/platform/assert.h"

/* =========================================================================
 * PLATFORM-SPECIFIC HEADERS
 * ========================================================================= */

#if TF_OS == TF_OS_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#elif TF_OS == TF_OS_LINUX

#include <errno.h>
#include <time.h>
#include <unistd.h>

#endif

/* =========================================================================
 * INTERNAL STATE
 * ========================================================================= */

static tf_u64 g_timer_frequency = 0;
static tf_u64 g_timer_start_ticks = 0;
static tf_b8 g_timer_initialized = TF_FALSE;

/* =========================================================================
 * IMPLEMENTATION
 * ========================================================================= */

void tf_timer_init(void) {
    if (g_timer_initialized) {
        return;
    }

#if TF_OS == TF_OS_WINDOWS

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    g_timer_frequency = (tf_u64)freq.QuadPart;

    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    g_timer_start_ticks = (tf_u64)counter.QuadPart;

#elif TF_OS == TF_OS_LINUX

    g_timer_frequency = 1000000000ULL; /* 1 GHz / nanosecond resolution */

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    g_timer_start_ticks = (tf_u64)ts.tv_sec * 1000000000ULL + (tf_u64)ts.tv_nsec;

#endif

    g_timer_initialized = TF_TRUE;
}

tf_u64 tf_timer_get_ticks(void) {
    if (!g_timer_initialized) {
        tf_timer_init();
    }

#if TF_OS == TF_OS_WINDOWS

    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return (tf_u64)counter.QuadPart;

#elif TF_OS == TF_OS_LINUX

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (tf_u64)ts.tv_sec * 1000000000ULL + (tf_u64)ts.tv_nsec;

#else
    return 0;
#endif
}

tf_u64 tf_timer_get_frequency(void) {
    if (!g_timer_initialized) {
        tf_timer_init();
    }

    return g_timer_frequency;
}

tf_f64 tf_timer_get_time_seconds(void) {
    if (!g_timer_initialized) {
        tf_timer_init();
    }

    tf_u64 current_ticks = tf_timer_get_ticks();
    tf_u64 elapsed_ticks = current_ticks - g_timer_start_ticks;

    return (tf_f64)elapsed_ticks / (tf_f64)g_timer_frequency;
}

tf_timer tf_timer_start(void) {
    tf_timer t;
    t.start_ticks = tf_timer_get_ticks();
    return t;
}

tf_f64 tf_timer_elapsed_seconds(const tf_timer *timer) {
    if (!timer) {
        return 0.0;
    }

    tf_u64 current_ticks = tf_timer_get_ticks();
    tf_u64 elapsed_ticks = current_ticks - timer->start_ticks;

    return (tf_f64)elapsed_ticks / (tf_f64)tf_timer_get_frequency();
}

tf_f64 tf_timer_elapsed_milliseconds(const tf_timer *timer) {
    return tf_timer_elapsed_seconds(timer) * 1000.0;
}

tf_f64 tf_timer_restart(tf_timer *timer) {
    if (!timer) {
        return 0.0;
    }

    tf_u64 current_ticks = tf_timer_get_ticks();
    tf_u64 elapsed_ticks = current_ticks - timer->start_ticks;
    timer->start_ticks = current_ticks;

    return (tf_f64)elapsed_ticks / (tf_f64)tf_timer_get_frequency();
}

void tf_timer_sleep(tf_u32 ms) {
#if TF_OS == TF_OS_WINDOWS

    Sleep((DWORD)ms);

#elif TF_OS == TF_OS_LINUX

    struct timespec ts;
    ts.tv_sec = (time_t)(ms / 1000u);
    ts.tv_nsec = (long)((ms % 1000u) * 1000000u);

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR) {
    }

#endif
}