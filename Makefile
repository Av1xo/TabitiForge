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