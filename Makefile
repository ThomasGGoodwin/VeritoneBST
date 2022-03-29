all: test

run: test
	./test

clean:
	rm -f test

test: BSTree.h main.cpp
	g++ -std=c++17 -o test main.cpp