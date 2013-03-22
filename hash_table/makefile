

CC = g++
CFLAGS = -g -Wall
OBJDIR = obj

OBJECTS = hash_table.o unit_test.o

unit_test: $(OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(OBJECTS)

hash_table.o: hash_table.cpp hash_table.h
	$(CC) $(CFLAGS) -c hash_table.cpp

unit_test.o: unit_test.cpp
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS) 

