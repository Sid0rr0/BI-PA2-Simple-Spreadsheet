FLAGS=-Wall -pedantic -Wextra -g -std=c++11 -c


all: compile


compile: lethanhh
	

lethanhh: build/main.o build/CCell.o build/CFunction.o build/CNumber.o build/CString.o build/COperation.o build/CTable.o build/CCursor.o
		mkdir -p build
		g++ build/main.o build/CCell.o build/CFunction.o build/CNumber.o build/CString.o build/COperation.o build/CTable.o build/CCursor.o -lncurses -o lethanhh

run: compile
		./lethanhh

doc:
		cd ./src && doxygen doxygen.conf

clean:
		rm -rf ./lethanhh
		rm -rf ./build
		rm -rf ./doc
		rm -ff ./src/latex

build/main.o: src/CCell.cpp src/CFunction.cpp src/CNumber.cpp src/CString.cpp src/COperation.cpp src/CTable.cpp src/CCursor.cpp
		mkdir -p build
		g++ $(FLAGS) src/main.cpp -o build/main.o

build/CCell.o: src/CCell.cpp
		mkdir -p build
		g++ $(FLAGS) src/CCell.cpp -o build/CCell.o

build/CFunction.o: src/CFunction.cpp
		mkdir -p build
		g++ $(FLAGS) src/CFunction.cpp -o build/CFunction.o

build/CNumber.o: src/CNumber.cpp
		mkdir -p build
		g++ $(FLAGS) src/CNumber.cpp -o build/CNumber.o

build/CString.o: src/CString.cpp
		mkdir -p build
		g++ $(FLAGS) src/CString.cpp -o build/CString.o

build/COperation.o: src/COperation.cpp
		mkdir -p build
		g++ $(FLAGS) src/COperation.cpp -o build/COperation.o

build/CTable.o: src/CTable.cpp
		mkdir -p build
		g++ $(FLAGS) src/CTable.cpp -o build/CTable.o

build/CCursor.o: src/CCursor.cpp
		mkdir -p build
		g++ $(FLAGS) src/CCursor.cpp -o build/CCursor.o