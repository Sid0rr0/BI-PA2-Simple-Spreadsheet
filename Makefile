all: compile


compile: lethanhh
		

lethanhh:
		g++ src/main.cpp src/CCell.cpp src/CFunction.cpp src/CNumber.cpp src/CString.cpp src/COperation.cpp src/CTable.cpp -lncurses -o lethanhh

run: clean compile
		./lethanhh

clean:
		rm -rf lethanhh
