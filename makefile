all: prepare analyze build build-docs build-example
docs: build-docs
examples: prepare build build-example
run: run-example-read
grind: grind-example-read

prepare:
	cmake -B staging -DCMAKE_BUILD_TYPE=Debug

clean:
	rm -rf staging

build:
	cmake --build staging

build-example:
	cmake --build staging --target tempora-example-read

build-docs:
	@echo "Building docxygen documentation to docs/html ..."
	@doxygen docs/Doxyfile > docs/Doxyfile.log 2> docs/Doxyfile.err.log

run-example-read:
	staging/./tempora-example-read

grind-example-read:
	valgrind --leak-check=full staging/tempora-example-read

analyze:
	@echo "Running static code check ..."
	@cppcheck --std=c11 \
		--enable=warning --enable=style \
		--includes-file=etc/analyze-include-dirs.list \
		--file-list=etc/analyze-source-files.list