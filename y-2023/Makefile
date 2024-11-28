CXX = g++
CXXFLAGS = -std=c++17

DAYS = $(shell seq -w 1 24)

all: day_$(DAYS)

reader:
	$(CXX) $(CXXFLAGS) -c ../include/reader.cpp

day_$(DAYS): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $@.cpp $<.o
	./$@.exe

clean:
	rm *.o *.exe