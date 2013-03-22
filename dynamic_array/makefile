

CC = g++
CFLAGS = -g -Wall
OBJDIR = obj

OBJECTS = dynamic_array.o unit_test.o

unit_test: $(OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(OBJECTS)

dynamic_array.o: dynamic_array.cc dynamic_array.hh dynamic_array.hxx
	$(CC) $(CFLAGS) -c dynamic_array.cc

unit_test.o: unit_test.cpp
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)

