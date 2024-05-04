CC=g++
CXXFLAGS=-Wall -c
# Path to asio
ASIO=-I../lib/include
PTHREAD=-pthread

# Build depends on main target
build: main

# Creates an executable called main
main: board.o piece.o space.o game.o
	$(CC) $(ASIO) $(PTHREAD) -o main main.cc space.o board.o piece.o game.o

# Creates an object file for space
space.o: space.cc space.h
	$(CC) $(CXXFLAGS) space.cc

# Creates an object file for piece
piece.o: piece.cc piece.h
	$(CC) $(CXXFLAGS) piece.cc

# Creates an object file for board
board.o: board.cc board.h
	$(CC) $(CXXFLAGS) board.cc

# Creates an object file for game
game.o: game.h game.cc
	$(CC) $(CXXFLAGS) game.cc	

# Clean removes any executables or object files
clean:
	rm main *.o