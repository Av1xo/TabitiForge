# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

import math
import pytest

from bindings.mat3x3 import Mat3x3
from bindings.vec3 import Vec3


def test_mat3x3_init_variants():
    m1 = Mat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9)
    assert list(m1.flat) == [float(i) for i in range(1, 10)]
    assert m1.m[0][0] == 1.0 and m1.m[2][2] == 9.0

    r0, r1, r2 = Vec3(1, 2, 3), Vec3(4, 5, 6), Vec3(7, 8, 9)
    m2 = Mat3x3(r0, r1, r2)
    assert m2.row[0].x == 1.0 and m2.row[2].z == 9.0
    assert m1.eq(m2)

    m_empty = Mat3x3()
    assert list(m_empty.flat) == [0.0] * 9


def test_mat3x3_construction_errors():
    with pytest.raises(TypeError, match="expects 9 scalars or 3 Vec3 objects"):
        Mat3x3(1, 2, 3)

    with pytest.raises(TypeError, match="expects 9 scalars or 3 Vec3 objects"):
        Mat3x3(Vec3(1, 0, 0), Vec3(0, 1, 0))


def test_mat3x3_factories():
    eye = Mat3x3.identity()
    assert eye.flat[0] == 1.0 and eye.flat[4] == 1.0 and eye.flat[8] == 1.0
    assert eye.flat[1] == 0.0 and eye.flat[3] == 0.0

    zero = Mat3x3.zero()
    assert all(v == 0.0 for v in zero.flat)

    nan_m = Mat3x3.nan()
    assert all(math.isnan(v) for v in nan_m.flat)

    m_rows = Mat3x3.from_rows(Vec3(1, 0, 0), Vec3(0, 2, 0), Vec3(0, 0, 3))
    assert m_rows.m[0][0] == 1.0 and m_rows.m[1][1] == 2.0 and m_rows.m[2][2] == 3.0


def test_mat3x3_repr():
    m = Mat3x3.identity()
    r = repr(m)
    assert "Mat3x3(" in r
    assert "[1.0000, 0.0000, 0.0000]" in r
