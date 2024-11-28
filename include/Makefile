CXX = g++
CXXFLAGS = -std=c++17

all: compile run clean

compile:
	$(CXX) $(CXXFLAGS) -c reader.cpp
	$(CXX) $(CXXFLAGS) -o readerTest.exe readerTests.cpp reader.o -lCatch2Main -lCatch2
run:
	./readerTest.exe

clean:
	rm *.o *.exe