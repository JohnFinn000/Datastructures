
CC = g++
CFLAGS = -g -Wall
OBJDIR = obj

OBJECTS = sort_unittest.o utilities.o radix_sort.o

unit_test: $(OBJECTS)
	$(CC) $(FLAGS) -o unit_test $(OBJECTS)

sort_unittest.o: unittests/sort_unittest.cpp bubble_sort.hxx insertion_sort.hxx selection_sort.hxx merge_sort.hxx unsort.hxx sort.h
	$(CC) $(CFLAGS) -c unittests/sort_unittest.cpp

radix_sort.o: radix_sort.cpp
	$(CC) $(CFLAGS) -c radix_sort.cpp

utilities.o: utilities.hh utilities.hxx utilities.cpp
	$(CC) $(CFLAGS) -c utilities.cpp

clean:
	rm unit_test $(OBJECTS)

