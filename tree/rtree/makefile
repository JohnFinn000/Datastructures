
CC = g++ 
CFLAGS = -g -Wall
OBJDIR = obj 

OBJECTS = point.o shape.o rtree_node.o rtree.o unit_test.o ../../lazy_eval/lazy_eval.o

unit_test: $(OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(OBJECTS)

point.o: point.cpp point.h hilbert_tables.h
	$(CC) $(CFLAGS) -c point.cpp

shape.o: shape.cpp shape.h
	$(CC) $(CFLAGS) -c shape.cpp

rtree_node.o: rtree_node.cpp rtree.h point.h shape.h
	$(CC) $(CFLAGS) -c rtree_node.cpp

rtree.o: rtree.cpp rtree.h point.h shape.h
	$(CC) $(CFLAGS) -c rtree.cpp

../../lazy_eval/lazy_eval.o: ../../lazy_eval/lazy_eval.cpp ../../lazy_eval/lazy_eval.h ../../lazy_eval/lazy_eval.hxx
	make lazy_eval.o -C ../../lazy_eval

unit_test.o: unit_test.cpp
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)


