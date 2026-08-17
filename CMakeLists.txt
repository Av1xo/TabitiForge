cmake_minimum_required(VERSION 3.20)

project(TabitiForge
    VERSION 0.0.001
    DESCRIPTION "Molecular simulation and artificial life platform"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

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