




CC = g++ 
CFLAGS = -g -Wall
OBJDIR = obj 

OBJECTS = rtree.o unittest.o

unit_test: $(OBJECTS)
    $(CC) $(CFLAGS) -o unit_test $(OBJECTS)

rtree.o: rtree.cpp rtree.h
    $(CC) $(CFLAGS) -c rtree.cpp

unit_test.o: unit_test.cpp
    $(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)


