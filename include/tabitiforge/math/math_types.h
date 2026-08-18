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

// double (IEEE 754)
#define TF_EPS_MATH   1e-15 // (~10*DBL_EPSILON)
#define TF_EPS_LEN    1e-9  // det(M), normalize(vec)
#define TF_EPS_LEN_SQ 1e-18 // (1e-9)^2
#define TF_EPS_SQ     1e-12 // (len^2)
#define TF_EPS_DENOM  1e-12 // (DivByZero guard)

#endif // TABITIFORGE_MATH_TYPES_H