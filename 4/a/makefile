all: main clean

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cpp d_except.h d_matrix.h main.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *o main
	echo clean
