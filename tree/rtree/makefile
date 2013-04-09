
CC = g++ 
CFLAGS = -g -Wall
OBJDIR = obj 

OBJECTS = point.o shape.o rtree.o unit_test.o

unit_test: $(OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(OBJECTS)

point.o: point.cpp point.h
	$(CC) $(CFLAGS) -c point.cpp

shape.o: shape.cpp shape.h
	$(CC) $(CFLAGS) -c shape.cpp

rtree.o: rtree.cpp rtree.h point.h shape.h
	$(CC) $(CFLAGS) -c rtree.cpp

unit_test.o: unit_test.cpp
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)


