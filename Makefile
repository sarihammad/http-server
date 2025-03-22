CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/server.c
OUT = server

all:
	# gcc -Wall -Wextra -Iinclude src/main.c src/server.c -o server -lpthread
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) -lpthread

clean:
	rm -f *.o $(OUT)