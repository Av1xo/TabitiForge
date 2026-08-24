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

#ifndef TABITIFORGE_PLATFORM_ASSERT_H
#define TABITIFORGE_PLATFORM_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#include "tabitiforge/platform/types.h"

/* =========================================================================
 * STATIC ASSERT
 * ========================================================================= */

/*
 * Compile-time assertion.
 *
 * C11 _Static_assert is used directly because TabitiForge targets C11+.
 */

#define TF_STATIC_ASSERT(condition, message) _Static_assert((condition), message)

/* =========================================================================
 * RUNTIME ASSERTS
 * ========================================================================= */

#if TF_BUILD == TF_DEBUG

/*
 * Internal assertion failure handler.
 *
 * This macro prints diagnostic information, flushes stderr and
 * triggers the platform/compiler-specific debugger break.
 */

#define TF_ASSERT_HALT(expr_str, file, line, msg_fmt, ...)                                         \
    do {                                                                                           \
        fprintf(stderr,                                                                            \
                "\n[TABITIFORGE ASSERT FAILED]\n"                                                  \
                "  Expression : %s\n"                                                              \
                "  File       : %s:%d\n"                                                           \
                "  Message    : " msg_fmt "\n\n",                                                  \
                (expr_str), (file), (line), ##__VA_ARGS__);                                        \
        fflush(stderr);                                                                            \
        TF_DEBUG_BREAK();                                                                          \
    } while (0)

/*
 * Assertion with formatted diagnostic message.
 */

#define TF_ASSERT_MSG(condition, msg_fmt, ...)                                                     \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            TF_ASSERT_HALT(#condition, __FILE__, __LINE__, msg_fmt, ##__VA_ARGS__);                \
        }                                                                                          \
    } while (0)

/*
 * Basic assertion without additional diagnostic information.
 */

#define TF_ASSERT(condition) TF_ASSERT_MSG(condition, "No details provided")

#else

/*
 * Assertions are completely disabled in release builds.
 *
 * Therefore the expression is not evaluated.
 */

#define TF_ASSERT(condition) ((void)0)

#define TF_ASSERT_MSG(condition, msg_fmt, ...) ((void)0)

#endif /* TF_BUILD == TF_DEBUG */

#endif /* TABITIFORGE_PLATFORM_ASSERT_H */