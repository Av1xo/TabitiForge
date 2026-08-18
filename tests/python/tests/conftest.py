# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

import ctypes
import os
import sys
from contextlib import suppress
from pathlib import Path

import pytest


PYTHON_DIR = Path(__file__).resolve().parents[1]

if str(PYTHON_DIR) not in sys.path:
    sys.path.insert(0, str(PYTHON_DIR))


@pytest.hookimpl(trylast=True)
def pytest_sessionfinish(session, exitstatus):
    lib_path = os.environ.get("TABITIFORGE_LIB_PATH")

    if lib_path and os.path.exists(lib_path):
        with suppress(OSError, AttributeError):
            core_lib = ctypes.CDLL(lib_path)
            if hasattr(core_lib, "__gcov_dump"):
                core_lib.__gcov_dump()
                return
            if hasattr(core_lib, "__gcov_flush"):
                core_lib.__gcov_flush()
                return

    with suppress(OSError, AttributeError):
        libc = ctypes.CDLL(None)
        if hasattr(libc, "__gcov_dump"):
            libc.__gcov_dump()
        elif hasattr(libc, "__gcov_flush"):
            libc.__gcov_flush()
