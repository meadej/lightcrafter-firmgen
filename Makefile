make: firmgen.cpp
	g++ -std=c++11 -o firmgen firmgen.cpp
clean: 
	rm -f firmgen firmware.bin
