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

cmake_minimum_required(VERSION 3.20)

project(TabitiForge
    VERSION 0.0.001
    DESCRIPTION "Molecular simulation and artificial life platform"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(TF_ENABLE_COVERAGE "Enable code coverage" OFF)

# ===============================
# CORE
# ===============================

add_library(tabitiforge_core SHARED
    src/math/vec3.c
)

target_include_directories(tabitiforge_core
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# ===============================
# APPLICATION
# ===============================

add_executable(tabitiforge
    src/main.c
)

target_link_libraries(tabitiforge
    PRIVATE
        tabitiforge_core
)

target_include_directories(tabitiforge
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# ===============================
# COVERAGE
# ===============================


if(TF_ENABLE_COVERAGE)
    target_compile_options(tabitiforge_core PRIVATE
        --coverage
        -O0
        -g
        -fprofile-abs-path
    )

    target_link_options(tabitiforge_core PRIVATE
        --coverage
    )
endif()