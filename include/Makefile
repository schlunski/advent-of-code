CXX = g++
CXXFLAGS = -std=c++17 -O3

all: compile-reader compile-structures run-reader clean

reader: compile-reader run-reader clean

structures: compile-structures run-structures clean

compile-reader:
	$(CXX) $(CXXFLAGS) -c reader.cpp
	$(CXX) $(CXXFLAGS) -o readerTest.exe readerTests.cpp reader.o -lCatch2Main -lCatch2

compile-structures:
	$(CXX) $(CXXFLAGS) -o structuresTest.exe structuresTest.cpp -lCatch2Main -lCatch2

run-reader:
	./readerTest.exe

run-structures:
	./structuresTest.exe

clean:
	rm *.o *.exe