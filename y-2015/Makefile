CXX = g++
CXXFLAGS = -std=c++17 -O3

DAY = $(addprefix day_, $(shell seq -w 1 24))
DAYDEBUG = $(addsuffix _debug, $(DAY))
DAYPUZZLEONE = $(addsuffix _puzzle_one, $(DAY))
DAYPUZZLEONEDEBUG = $(addsuffix _puzzle_one_debug, $(DAY))
DAYPUZZLETWO = $(addsuffix _puzzle_two, $(DAY))
DAYPUZZLETWODEBUG = $(addsuffix _puzzle_two_debug, $(DAY))

reader:
	$(CXX) $(CXXFLAGS) -c ../include/reader.cpp

$(DAY): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $@.cpp $<.o
	./$@.exe 0 0

$(DAYDEBUG): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $(subst _debug,, $@).cpp $<.o
	./$@.exe 0 1

$(DAYPUZZLEONE): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $(subst _puzzle_one,, $@).cpp $<.o
	./$@.exe 1 0 

$(DAYPUZZLEONEDEBUG): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $(subst _puzzle_one_debug,, $@).cpp $<.o
	./$@.exe 1 1

$(DAYPUZZLETWO): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $(subst _puzzle_two,, $@).cpp $<.o
	./$@.exe 2 0

$(DAYPUZZLETWODEBUG): reader
	$(CXX) $(CXXFLAGS) -o $@.exe $(subst _puzzle_two_debug,, $@).cpp $<.o
	./$@.exe 2 1


clean:
	rm *.o *.exe