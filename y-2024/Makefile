CXX = g++
CXXFLAGS = -std=c++17 -O3

DAYS = $(addprefix day_, $(shell seq -w 1 24))
DAYSDEBUG = $(addsuffix _debug, $(DAYS))

reader:
	$(CXX) $(CXXFLAGS) -c ../include/reader.cpp

$(DAYS): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $@.cpp $<.o
	./$@.exe

$(DAYSDEBUG): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $(subst _debug,, $@).cpp $<.o
	./$@.exe debug

clean:
	rm *.o *.exe