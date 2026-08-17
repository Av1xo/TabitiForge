#
# Copyright 2026 Rostyslav Zhurbenko
#
# SPDX-License-Identifier: Apache-2.0
#

from pathlib import Path
import ctypes

ROOT_DIR = Path(__file__).resolve().parents[3]
BUILD_DIR = ROOT_DIR / "build-coverage"

LIBRARY_PATH = BUILD_DIR / "libtabitiforge_core.so"

lib = ctypes.CDLL(str(LIBRARY_PATH))
