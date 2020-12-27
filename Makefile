EXENAME = main
OBJS = maze.o tile.o disjoint-sets.o Animation.o PNG.o HSLAPixel.o lodepng.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O2 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all : $(EXENAME)

$(EXENAME) : main.o $(OBJS) 
	$(CXX) main.o $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp maze.h
	$(CXX) $(CXXFLAGS) main.cpp

maze.o : maze.cpp tile.h disjoint-sets.h png/Animation.h png/PNG.h
	$(CXX) $(CXXFLAGS) maze.cpp

tile.o : tile.cpp
	$(CXX) $(CXXFLAGS) tile.cpp

disjoint-sets.o : disjoint-sets.cpp
	$(CXX) $(CXXFLAGS) disjoint-sets.cpp

Animation.o : png/Animation.cpp png/PNG.h
	$(CXX) $(CXXFLAGS) png/Animation.cpp

PNG.o : png/PNG.cpp png/HSLAPixel.h png/RGB_HSL.h png/lodepng.h
	$(CXX) $(CXXFLAGS) png/PNG.cpp

HSLAPixel.o : png/HSLAPixel.cpp
	$(CXX) $(CXXFLAGS) png/HSLAPixel.cpp

lodepng.o : png/lodepng.cpp
	$(CXX) $(CXXFLAGS) png/lodepng.cpp

clean:
	-rm -f *.o $(EXENAME)