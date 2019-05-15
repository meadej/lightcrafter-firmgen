make: firmgen.cpp;
    gcc -std=c++11 -o firmgen firmgen.cpp -I;
clean: rm firmgen