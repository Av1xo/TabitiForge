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

BUILD_DIR := build
COVERAGE_BUILD_DIR := build-coverage

.PHONY: configure build test run clean rebuild \
        coverage-configure coverage-build coverage-test coverage-report coverage

configure:
	cmake -S . -B $(BUILD_DIR)

build: configure
	cmake --build $(BUILD_DIR)

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

run: build
	./$(BUILD_DIR)/tabitiforge

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean build


coverage-configure:
	cmake -S . -B $(COVERAGE_BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DTF_ENABLE_COVERAGE=ON


coverage-build: coverage-configure
	cmake --build $(COVERAGE_BUILD_DIR)


coverage-test: coverage-build
	pytest tests/python/tests


coverage-report: coverage-test
	rm -rf $(COVERAGE_BUILD_DIR)/CMakeFiles/3.28.3/CompilerIdC
	gcovr \
		--root . \
		--object-directory $(COVERAGE_BUILD_DIR) \
		--filter 'src/.*\.c$$' \
		--print-summary


coverage: coverage-report