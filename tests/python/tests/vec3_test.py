#
# Copyright 2026 Rostyslav Zhurbenko
#
# SPDX-License-Identifier: Apache-2.0
#

import ctypes
from bindings.vec3 import Vec3, lib


def test_vec3_add():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    
    result = lib.vec3_add(a, b)
    
    assert result.x == 5.0
    assert result.y == 7.0
    assert result.z == 9.0

def test_vec3_iadd():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)

    lib.vec3_iadd(ctypes.byref(a), b)

    assert a.x == 5.0
    assert a.y == 7.0
    assert a.z == 9.0