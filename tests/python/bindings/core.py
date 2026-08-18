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
import os
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[3]

env_path = os.environ.get("TABITIFORGE_LIB_PATH")

if env_path and Path(env_path).exists():
    LIBRARY_PATH = Path(env_path)
else:
    candidate_paths = [
        PROJECT_ROOT / "build" / "libtabitiforge_core.so",
        PROJECT_ROOT / "build-coverage" / "libtabitiforge_core.so",
        PROJECT_ROOT / "build-sanitize" / "libtabitiforge_core.so",
    ]

    LIBRARY_PATH = None
    for path in candidate_paths:
        if path.exists():
            LIBRARY_PATH = path
            break

if not LIBRARY_PATH:
    raise FileNotFoundError(
        "Could not find libtabitiforge_core.so! "
        "Build the project first or set TABITIFORGE_LIB_PATH."
    )

lib = ctypes.CDLL(str(LIBRARY_PATH))
