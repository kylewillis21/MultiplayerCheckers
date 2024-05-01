CC=g++
CXXFLAGS=-Wall -c
# Path to asio
ASIO=-I./lib/include
PTHREAD=-pthread

# Build depends on main target
build: main

# Test creates an executable called test that was used for testing purposes
test: piece.o test.o space.o board.o game.o
	$(CC) -o test space.o piece.o test.o board.o game.o

# Creates an executable called main
main: game.o board.o piece.o space.o
	$(CC) $(ASIO) $(PTHREAD) -o main main.cc game.o board.o space.o piece.o

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

# Creates an object file for game
game.o: game.h game.cc
	$(CC) $(CXXFLAGS) game.cc
	
# Clean removes all .o files and main
clean:
	rm *.o main test