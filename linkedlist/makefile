

CC = g++
CFLAGS = -g -Wall
OBJDIR = obj

OBJECTS = list.o unit_test.o

unit_test: $(OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(OBJECTS)

list.o: list.cpp list.h
	$(CC) $(CFLAGS) -c list.cpp

unit_test.o: unit_test.cpp
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)

