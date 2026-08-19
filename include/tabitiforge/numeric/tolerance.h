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

#ifndef TABITIFORGE_NUMERIC_TOLERANCE_H
#define TABITIFORGE_NUMERIC_TOLERANCE_H

#include "tabitiforge/numeric/types.h"

/* ========================================================================= */
/* TOLERANCE POLICY                                                          */
/* ========================================================================= */

/*
 * Multipliers are expressed relative to machine epsilon.
 *
 * These values are numerical policy parameters, not mathematical constants.
 * They can be overridden at compile-time if needed.
 */

#ifndef TF_TOL_ABS_MULT
#define TF_TOL_ABS_MULT 64.0L
#endif

#ifndef TF_TOL_REL_MULT
#define TF_TOL_REL_MULT 64.0L
#endif

#ifndef TF_TOL_ZERO_MULT
#define TF_TOL_ZERO_MULT 64.0L
#endif

#ifndef TF_TOL_DENOM_MULT
#define TF_TOL_DENOM_MULT 64.0L
#endif

#ifndef TF_TOL_GEOMETRY_MULT
#define TF_TOL_GEOMETRY_MULT 256.0L
#endif

#ifndef TF_TOL_DET_MULT
#define TF_TOL_DET_MULT 256.0L
#endif

/* ========================================================================= */
/* BASE TOLERANCES                                                           */
/* ========================================================================= */

#define TF_TOL_ABS      ((real_t)(TF_TOL_ABS_MULT * TF_REAL_EPSILON))
#define TF_TOL_REL      ((real_t)(TF_TOL_REL_MULT * TF_REAL_EPSILON))
#define TF_TOL_ZERO     ((real_t)(TF_TOL_ZERO_MULT * TF_REAL_EPSILON))
#define TF_TOL_ZERO_SQ  ((real_t)(TF_TOL_ZERO * TF_TOL_ZERO))
#define TF_TOL_DENOM    ((real_t)(TF_TOL_DENOM_MULT * TF_REAL_EPSILON))
#define TF_TOL_GEOMETRY ((real_t)(TF_TOL_GEOMETRY_MULT * TF_REAL_EPSILON))
#define TF_TOL_DET      ((real_t)(TF_TOL_DET_MULT * TF_REAL_EPSILON))

#endif /* TABITIFORGE_NUMERIC_TOLERANCE_H */