CXX = g++
CXXFLAGS = -std=c++17

DAYS = $(addprefix day_, $(shell seq -w 1 24))

reader:
	$(CXX) $(CXXFLAGS) -c ../include/reader.cpp

$(DAYS): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $@.cpp $<.o
	./$@.exe

clean:
	rm *.o *.exe