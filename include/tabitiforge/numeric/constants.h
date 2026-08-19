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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TABITIFORGE_NUMERIC_CONSTANTS_H
#define TABITIFORGE_NUMERIC_CONSTANTS_H

#include "tabitiforge/numeric/types.h"

/* ========================================================================= */
/* MATHEMATICAL CONSTANTS                                                    */
/* ========================================================================= */

#define TF_PI     ((real_t)3.141592653589793238462643383279502884L)
#define TF_TAU    ((real_t)(2.0L * TF_PI))
#define TF_TWO_PI TF_TAU

#define TF_HALF_PI    ((real_t)(0.5L * TF_PI))
#define TF_QUARTER_PI ((real_t)(0.25L * TF_PI))

#define TF_INV_PI  ((real_t)(1.0L / TF_PI))
#define TF_INV_TAU ((real_t)(1.0L / TF_TAU))

#define TF_E ((real_t)2.718281828459045235360287471352662498L)

#define TF_SQRT2     ((real_t)1.414213562373095048801688724209698079L)
#define TF_INV_SQRT2 ((real_t)0.707106781186547524400844362104849039L)

#define TF_SQRT3     ((real_t)1.732050807568877293527446341505872367L)
#define TF_INV_SQRT3 ((real_t)0.577350269189625764509148780501957456L)

/* ========================================================================= */
/* ANGLE CONVERSION CONSTANTS                                                */
/* ========================================================================= */

#define TF_DEG_PER_RAD ((real_t)(180.0L / TF_PI))
#define TF_RAD_PER_DEG ((real_t)(TF_PI / 180.0L))

#endif /* TABITIFORGE_NUMERIC_CONSTANTS_H */