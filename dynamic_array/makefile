

CC = g++
CFLAGS = -g -Wall
OBJDIR = obj

OBJECTS = unit_test.o

unit_test: $(OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(OBJECTS)

unit_test.o: unit_test.cpp dynamic_array.hh dynamic_array.hxx
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)

