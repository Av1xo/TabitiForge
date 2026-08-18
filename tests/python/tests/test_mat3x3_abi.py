# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

import ctypes

from bindings.core import lib
from bindings.mat3x3 import Mat3x3


def test_mat3x3_memory_layout():
    # 9 * double (8 bytes) = 72 bytes
    assert ctypes.sizeof(Mat3x3) == 72

    m = Mat3x3.identity()

    m.flat[0] = 42.0
    assert m.m[0][0] == 42.0
    assert m.row[0].x == 42.0

    m.m[1][1] = 99.0
    assert m.flat[4] == 99.0
    assert m.row[1].y == 99.0

    m.row[2].z = 77.0
    assert m.flat[8] == 77.0
    assert m.m[2][2] == 77.0


def test_mat3x3_by_reference_mutability():
    m = Mat3x3.identity()

    lib.mat3x3_iscale(ctypes.byref(m), 2.0)

    expected = Mat3x3(
        2.0,
        0.0,
        0.0,
        0.0,
        2.0,
        0.0,
        0.0,
        0.0,
        2.0,
    )

    assert m.eps_eq(expected, 1e-12)
