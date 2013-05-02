
CC = g++ 
CFLAGS = -g -Wall
OBJDIR = obj 

LAZYDIR = ../../lazy_eval

OBJECTS = point.o shape.o rtree.o rtree_node.o unit_test.o $(LAZYDIR)/lazy_eval.o

unit_test: $(OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(OBJECTS)

point.o: point.cpp point.h hilbert_tables.h
	$(CC) $(CFLAGS) -c point.cpp

shape.o: shape.cpp shape.h point.h
	$(CC) $(CFLAGS) -c shape.cpp

rtree_node.o: rtree_node.cpp rtree.h point.h shape.h
	$(CC) $(CFLAGS) -c rtree_node.cpp

rtree.o: rtree.cpp rtree.h point.h shape.h
	$(CC) $(CFLAGS) -c rtree.cpp

$(LAZYDIR)/lazy_eval.o: $(LAZYDIR)/lazy_eval.cpp $(LAZYDIR)/lazy_eval.h $(LAZYDIR)/lazy_eval.hxx
	make lazy_eval.o -C $(LAZYDIR)

unit_test.o: unit_test.cpp
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)


