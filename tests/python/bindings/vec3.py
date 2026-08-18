# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# TabitiForge Simulation Engine
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

import ctypes

from .core import lib


class Vec3(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_double),
        ("y", ctypes.c_double),
        ("z", ctypes.c_double),
    ]

    def __repr__(self):
        return f"Vec3({self.x:.4f}, {self.y:.4f}, {self.z:.4f})"


VEC3_ZERO = Vec3(0.0, 0.0, 0.0)

lib.vec3_add.argtypes = [Vec3, Vec3]
lib.vec3_add.restype = Vec3

lib.vec3_iadd.argtypes = [ctypes.POINTER(Vec3), Vec3]
lib.vec3_iadd.restype = None

lib.vec3_sub.argtypes = [Vec3, Vec3]
lib.vec3_sub.restype = Vec3

lib.vec3_isub.argtypes = [ctypes.POINTER(Vec3), Vec3]
lib.vec3_isub.restype = None

lib.vec3_scale.argtypes = [Vec3, ctypes.c_double]
lib.vec3_scale.restype = Vec3

lib.vec3_iscale.argtypes = [ctypes.POINTER(Vec3), ctypes.c_double]
lib.vec3_iscale.restype = None

lib.vec3_dot.argtypes = [Vec3, Vec3]
lib.vec3_dot.restype = ctypes.c_double

lib.vec3_cross.argtypes = [Vec3, Vec3]
lib.vec3_cross.restype = Vec3

lib.vec3_len.argtypes = [Vec3]
lib.vec3_len.restype = ctypes.c_double

lib.vec3_len2.argtypes = [Vec3]
lib.vec3_len2.restype = ctypes.c_double

lib.vec3_norm.argtypes = [Vec3]
lib.vec3_norm.restype = Vec3

lib.vec3_inorm.argtypes = [ctypes.POINTER(Vec3)]
lib.vec3_inorm.restype = None

lib.vec3_dist.argtypes = [Vec3, Vec3]
lib.vec3_dist.restype = ctypes.c_double

lib.vec3_proj.argtypes = [Vec3, Vec3]
lib.vec3_proj.restype = Vec3

lib.vec3_reflect.argtypes = [Vec3, Vec3]
lib.vec3_reflect.restype = Vec3

lib.vec3_nreflect.argtypes = [Vec3, Vec3]
lib.vec3_nreflect.restype = Vec3

lib.vec3_neg.argtypes = [Vec3]
lib.vec3_neg.restype = Vec3

lib.vec3_ineg.argtypes = [ctypes.POINTER(Vec3)]
lib.vec3_ineg.restype = None

lib.vec3_mul.argtypes = [Vec3, Vec3]
lib.vec3_mul.restype = Vec3

lib.vec3_imul.argtypes = [ctypes.POINTER(Vec3), Vec3]
lib.vec3_imul.restype = None

lib.vec3_clamp.argtypes = [Vec3, ctypes.c_double]
lib.vec3_clamp.restype = Vec3

lib.vec3_iclamp.argtypes = [ctypes.POINTER(Vec3), ctypes.c_double]
lib.vec3_iclamp.restype = None

lib.vec3_lerp.argtypes = [Vec3, Vec3, ctypes.c_double]
lib.vec3_lerp.restype = Vec3

lib.vec3_ilerp.argtypes = [ctypes.POINTER(Vec3), Vec3, ctypes.c_double]
lib.vec3_ilerp.restype = None

lib.vec3_angle_between.argtypes = [Vec3, Vec3]
lib.vec3_angle_between.restype = ctypes.c_double

lib.vec3_abs.argtypes = [Vec3]
lib.vec3_abs.restype = Vec3

lib.vec3_iabs.argtypes = [ctypes.POINTER(Vec3)]
lib.vec3_iabs.restype = None

lib.vec3_eq.argtypes = [Vec3, Vec3]
lib.vec3_eq.restype = ctypes.c_int

lib.vec3_rotate.argtypes = [Vec3, Vec3, ctypes.c_double]
lib.vec3_rotate.restype = Vec3

lib.vec3_nrotate.argtypes = [Vec3, Vec3, ctypes.c_double]
lib.vec3_nrotate.restype = Vec3
