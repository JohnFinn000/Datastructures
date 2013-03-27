

CC = g++
CFLAGS = -g -Wall
OBJDIR = obj

OBJECTS = list_iterator.o list.o unit_test.o

unit_test: $(OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(OBJECTS)

list_iterator.o: list_iterator.cpp list.h
	$(CC) $(CFLAGS) -c list_iterator.cpp

list.o: list.cpp list.h
	$(CC) $(CFLAGS) -c list.cpp

unit_test.o: unit_test.cpp
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)

