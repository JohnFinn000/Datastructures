
CC = g++
CFLAGS = -g -Wall
OBJDIR = obj

unit_test: unit_test.o
	$(CC) $(FLAGS) -o unit_test unit_test.o

unit_test.o: unit_test.cpp bubble_sort.hxx insertion_sort.hxx selection_sort.hxx merge_sort.hxx unsort.hxx sort.h
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test

