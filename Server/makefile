CC=g++
CXXFLAGS=-Wall -c

# Build depends on main target
build: main

# Main creates an executable called main
main: piece.o test.o space.o board.o
	$(CC) -o main space.o piece.o test.o board.o

# Creates an object file for piece
piece.o: piece.cc piece.h
	$(CC) $(CXXFLAGS) piece.cc

# Creates an object file for test
test.o: piece.h test.cc
	$(CC) $(CXXFLAGS) test.cc

# Creates an object file for space
space.o: space.cc space.h
	$(CC) $(CXXFLAGS) space.cc

# Creates an object file for board
board.o: board.cc board.h
	$(CC) $(CXXFLAGS) board.cc

# Clean removes all .o files and main
clean:
	rm *.o main