

CC = g++

CFLAGS = -c -Wall -Wextra

all : MyStack

MyStack : stack.o Functions.stack.o 
	$(CC) $^ -o $@

stack.o : stack.cpp
	$(CC) $(CFLAGS) $^

Functions.stack.o : Functions.stack.cpp
	$(CC) $(CFLAGS) $^

clean:
	rm -rf *.o MyStack

rebuild: clean all