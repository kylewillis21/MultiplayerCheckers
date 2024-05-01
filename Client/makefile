CC=g++
CXXFLAGS=-Wall -called
# Path to asio
ASIO=-I../lib/include
PTHREAD=-pthread

# Build depends on main target
build: main

# Creates an executable called main
main:
	$(CC) $(ASIO) $(PTHREAD) -o main main.cc

# Clean removes any executables or object files
clean:
	rm main *.o