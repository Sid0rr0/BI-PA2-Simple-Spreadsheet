all: compile


compile: lethanhh
		

lethanhh:
		g++ src/main.cpp src/CCell.cpp src/CFunction.cpp src/CNumber.cpp src/CString.cpp -o lethanhh

run: compile
		./lethanhh

clean:
		rm -rf lethanhh