BUILD_DIR := build

.PHONY: configure build test run clean rebuild

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