# Compiler to use
CC = gcc

# Compiler flags: warnings + include directory
CFLAGS = -Wall -Wextra -Iinclude

# Source files
SRC = src/main.c src/server.c

# Output binary name
OUT = server

# Default target
all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) -lpthread

# Clean up build artifacts
clean:
	rm -f $(OUT)