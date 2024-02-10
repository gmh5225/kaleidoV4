.PHONY: clean all

all: main

main:    driver.o parser.o scanner.o main.o
	clang++ -o main driver.o parser.o scanner.o main.o `llvm-config --cxxflags --ldflags --libs --libfiles --system-libs`

main.o:  main.cpp driver.hpp
	clang++ -c main.cpp -I/usr/lib/llvm-16/include -std=c++17 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
	
parser.o: parser.cpp
	clang++ -c parser.cpp -I/usr/lib/llvm-16/include -std=c++17 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
	
scanner.o: scanner.cpp parser.hpp
	clang++ -c scanner.cpp -I/usr/lib/llvm-16/include -std=c++17 -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS 
	
driver.o: driver.cpp parser.hpp driver.hpp
	clang++ -c driver.cpp -I/usr/lib/llvm-16/include -std=c++17 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS 

parser.cpp, parser.hpp: parser.yy 
	bison -o parser.cpp parser.yy

scanner.cpp: scanner.ll
	flex -o scanner.cpp scanner.ll

clean:
	rm -f *~ driver.o scanner.o parser.o main.o main scanner.cpp parser.cpp parser.hpp
