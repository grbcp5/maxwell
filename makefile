default: build

build:
	mkdir -p out
	g++ -g *.cpp -o out/a.out

run: build
	out/a.out test

valgrind: build
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all out/a.out test
