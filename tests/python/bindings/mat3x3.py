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
from .vec3 import Vec3


class Mat3x3(ctypes.Union):
    _fields_ = (
        ("m", (ctypes.c_double * 3) * 3),
        ("flat", ctypes.c_double * 9),
        ("row", Vec3 * 3),
    )

    def __init__(self, *args):
        super().__init__()

        if len(args) == 9:
            for i, val in enumerate(args):
                self.flat[i] = float(val)

        elif len(args) == 3 and all(isinstance(a, Vec3) for a in args):
            self.row[0] = args[0]
            self.row[1] = args[1]
            self.row[2] = args[2]

        elif len(args) != 0:
            raise TypeError("Mat3x3 expects 9 scalars or 3 Vec3 objects")

    @classmethod
    def from_rows(cls, a: Vec3, b: Vec3, c: Vec3) -> "Mat3x3":
        return cls(a, b, c)

    @classmethod
    def identity(cls) -> "Mat3x3":
        return cls(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)

    @classmethod
    def zero(cls) -> "Mat3x3":
        return cls(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)

    @classmethod
    def nan(cls) -> "Mat3x3":
        nan_val = float("nan")
        return cls(*[nan_val] * 9)

    def transpose(self) -> "Mat3x3":
        return lib.mat3x3_transpose(self)

    def itranspose(self) -> "Mat3x3":
        lib.mat3x3_itranspose(ctypes.byref(self))
        return self

    def vecmul(self, v: Vec3) -> Vec3:
        return lib.mat3x3_vecmul(v, self)

    def ivecmul(self, v: Vec3) -> Vec3:
        lib.mat3x3_ivecmul(ctypes.byref(v), self)
        return v

    def mul(self, b: "Mat3x3") -> "Mat3x3":
        return lib.mat3x3_mul(self, b)

    def imul(self, b: "Mat3x3") -> "Mat3x3":
        lib.mat3x3_imul(ctypes.byref(self), b)
        return self

    def add(self, b: "Mat3x3") -> "Mat3x3":
        return lib.mat3x3_add(self, b)

    def iadd(self, b: "Mat3x3") -> "Mat3x3":
        lib.mat3x3_iadd(ctypes.byref(self), b)
        return self

    def sub(self, b: "Mat3x3") -> "Mat3x3":
        return lib.mat3x3_sub(self, b)

    def isub(self, b: "Mat3x3") -> "Mat3x3":
        lib.mat3x3_isub(ctypes.byref(self), b)
        return self

    def neg(self) -> "Mat3x3":
        return lib.mat3x3_neg(self)

    def ineg(self) -> "Mat3x3":
        lib.mat3x3_ineg(ctypes.byref(self))
        return self

    def scale(self, s: float) -> "Mat3x3":
        return lib.mat3x3_scale(self, float(s))

    def iscale(self, s: float) -> "Mat3x3":
        lib.mat3x3_iscale(ctypes.byref(self), float(s))
        return self

    def det(self) -> float:
        return lib.mat3x3_det(self)

    def cofactor(self) -> "Mat3x3":
        return lib.mat3x3_cofactor(self)

    def inv(self) -> tuple[bool, "Mat3x3"]:
        out_inv = Mat3x3()
        ok = lib.mat3x3_inv(self, ctypes.byref(out_inv))
        return ok, out_inv

    @classmethod
    def outer(cls, a: Vec3, b: Vec3) -> "Mat3x3":
        return lib.mat3x3_outer(a, b)

    @classmethod
    def skew(cls, k: Vec3) -> "Mat3x3":
        return lib.mat3x3_skew(k)

    @classmethod
    def rotation(cls, k: Vec3, theta: float) -> "Mat3x3":
        return lib.mat3x3_rotation(k, float(theta))

    def trace(self) -> float:
        return lib.mat3x3_trace(self)

    def so3_angle_between(self, b: "Mat3x3") -> float:
        return lib.mat3x3_so3_angle_between(self, b)

    def angle_between(self, b: "Mat3x3") -> float:
        return lib.mat3x3_angle_between(self, b)

    def eq(self, b: "Mat3x3") -> bool:
        return lib.mat3x3_eq(self, b)

    def eps_eq(self, b: "Mat3x3", eps: float) -> bool:
        return lib.mat3x3_eps_eq(self, b, float(eps))

    def __repr__(self) -> str:
        rows = ",\n".join(
            f"  [{self.m[i][0]:.4f}, {self.m[i][1]:.4f}, {self.m[i][2]:.4f}]"
            for i in range(3)
        )
        return f"Mat3x3(\n{rows}\n)"


lib.mat3x3_transpose.argtypes = [Mat3x3]
lib.mat3x3_transpose.restype = Mat3x3

lib.mat3x3_itranspose.argtypes = [ctypes.POINTER(Mat3x3)]
lib.mat3x3_itranspose.restype = None

lib.mat3x3_vecmul.argtypes = [Vec3, Mat3x3]
lib.mat3x3_vecmul.restype = Vec3

lib.mat3x3_ivecmul.argtypes = [ctypes.POINTER(Vec3), Mat3x3]
lib.mat3x3_ivecmul.restype = None

lib.mat3x3_mul.argtypes = [Mat3x3, Mat3x3]
lib.mat3x3_mul.restype = Mat3x3

lib.mat3x3_imul.argtypes = [ctypes.POINTER(Mat3x3), Mat3x3]
lib.mat3x3_imul.restype = None

lib.mat3x3_add.argtypes = [Mat3x3, Mat3x3]
lib.mat3x3_add.restype = Mat3x3

lib.mat3x3_iadd.argtypes = [ctypes.POINTER(Mat3x3), Mat3x3]
lib.mat3x3_iadd.restype = None

lib.mat3x3_sub.argtypes = [Mat3x3, Mat3x3]
lib.mat3x3_sub.restype = Mat3x3

lib.mat3x3_isub.argtypes = [ctypes.POINTER(Mat3x3), Mat3x3]
lib.mat3x3_isub.restype = None

lib.mat3x3_neg.argtypes = [Mat3x3]
lib.mat3x3_neg.restype = Mat3x3

lib.mat3x3_ineg.argtypes = [ctypes.POINTER(Mat3x3)]
lib.mat3x3_ineg.restype = None

lib.mat3x3_scale.argtypes = [Mat3x3, ctypes.c_double]
lib.mat3x3_scale.restype = Mat3x3

lib.mat3x3_iscale.argtypes = [ctypes.POINTER(Mat3x3), ctypes.c_double]
lib.mat3x3_iscale.restype = None

lib.mat3x3_det.argtypes = [Mat3x3]
lib.mat3x3_det.restype = ctypes.c_double

lib.mat3x3_cofactor.argtypes = [Mat3x3]
lib.mat3x3_cofactor.restype = Mat3x3

lib.mat3x3_inv.argtypes = [Mat3x3, ctypes.POINTER(Mat3x3)]
lib.mat3x3_inv.restype = ctypes.c_bool

lib.mat3x3_outer.argtypes = [Vec3, Vec3]
lib.mat3x3_outer.restype = Mat3x3

lib.mat3x3_skew.argtypes = [Vec3]
lib.mat3x3_skew.restype = Mat3x3

lib.mat3x3_rotation.argtypes = [Vec3, ctypes.c_double]
lib.mat3x3_rotation.restype = Mat3x3

lib.mat3x3_trace.argtypes = [Mat3x3]
lib.mat3x3_trace.restype = ctypes.c_double

lib.mat3x3_so3_angle_between.argtypes = [Mat3x3, Mat3x3]
lib.mat3x3_so3_angle_between.restype = ctypes.c_double

lib.mat3x3_angle_between.argtypes = [Mat3x3, Mat3x3]
lib.mat3x3_angle_between.restype = ctypes.c_double

lib.mat3x3_eq.argtypes = [Mat3x3, Mat3x3]
lib.mat3x3_eq.restype = ctypes.c_bool

lib.mat3x3_eps_eq.argtypes = [Mat3x3, Mat3x3, ctypes.c_double]
lib.mat3x3_eps_eq.restype = ctypes.c_bool
