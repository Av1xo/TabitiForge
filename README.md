<!--
SPDX-FileCopyrightText: 2026 Rostyslav Zhurbenko, Valeriia Syrotenko

SPDX-License-Identifier: Apache-2.0
-->

# TabitiForge

> Open molecular simulation and artificial life research platform.

TabitiForge is an open-source project exploring molecular simulation,
computational biology and artificial life from the lowest level.

[![REUSE status](https://api.reuse.software/badge/github.com/Av1xo/TabitiForge)](https://api.reuse.software/info/github.com/Av1xo/TabitiForge)
[![License](https://img.shields.io/badge/Apache_2.0-active-green.svg)](https://opensource.org/license/apache-2.0)
## Goals

- Molecular representation
- Chemical bonds
- Molecular dynamics
- DNA / RNA modelling
- Genetic systems
- Artificial life
- GPU acceleration with Vulkan

## Current status

Early development

Currently implementing the mathematical and molecular foundations
of the simulation engine.

## USAGE
- First run
```bash
make build
```
- Run app
```bash
make run
```
- Run test
```bash
make test
```
- Rebuild
```bash
make rebuild
```
- Clean
```bash
make clean
```

------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: .
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
src/math/mat3x3.c                            134     134   100%
src/math/vec3.c                              121     121   100%
------------------------------------------------------------------------------
TOTAL                                        255     255   100%
------------------------------------------------------------------------------
lines: 100.0% (255 out of 255)
functions: 100.0% (55 out of 55)
branches: 100.0% (64 out of 64)
