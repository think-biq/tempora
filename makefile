all: prepare build

prepare:
	cmake -B staging

clean:
	rm -rf staging

build:
	cmake --build staging