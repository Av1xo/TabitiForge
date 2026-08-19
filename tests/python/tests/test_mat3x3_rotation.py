# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

import math

from bindings.mat3x3 import Mat3x3
from bindings.vec3 import Vec3


def test_mat3x3_rotation_orthogonal():
    axis = Vec3(1.0, 2.0, 3.0)
    angle = math.pi / 3.0

    rot = Mat3x3.rotation(axis, angle)

    # R^T * R == I
    res = rot.transpose().mul(rot)
    assert res.eps_eq(Mat3x3.identity(), 1e-6)

    # det(R) == 1
    assert abs(rot.det() - 1.0) < 1e-6


def test_mat3x3_rotation_zero_axis_edge_case():
    zero_axis = Vec3(0.0, 0.0, 0.0)
    rot = Mat3x3.rotation(zero_axis, 1.5)

    assert rot.eps_eq(Mat3x3.identity(), 1e-9)
