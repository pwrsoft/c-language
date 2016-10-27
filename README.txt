To compile and run the examples use one of these example commands:
	g++ -std=c++11 eventlog.cpp && ./a.out
	g++ -std=c++11 eventlog.cpp -o eventlog && ./eventlog

PS: Use g++ instead of gcc for compiling C++ code:
	g++ -Wall -W -Werror tex.cpp -o tex
gcc does not link stdc++ library by default which is required for your code.
