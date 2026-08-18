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
 * Unless required by applicable law or agreed to in writing,上下,
 * software distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TABITIFORGE_MATH_TYPES_H
#define TABITIFORGE_MATH_TYPES_H

#include <float.h>

/*
 * Numerical tolerances for mathematical operations.
 *
 * These values are NOT physical constants.
 * They define numerical decision thresholds only.
 */

/* Floating-point comparison / numerical noise. */
#define TF_EPS_MATH (10.0 * DBL_EPSILON)

/* Geometric zero threshold. */
#define TF_EPS_LENGTH 1e-9

/* Squared geometric zero threshold. */
#define TF_EPS_LENGTH_SQ (TF_EPS_LENGTH * TF_EPS_LENGTH)

/* Generic denominator guard. */
#define TF_EPS_DENOM 1e-12

/* Matrix determinant singularity threshold. */
#define TF_EPS_DET 1e-12

#endif // TABITIFORGE_MATH_TYPES_H