
CC = g++
CFLAGS = -g -Wall
OBJDIR = obj

OBJECTS = bubblesort.o insertionsort.o mergesort.o selectionsort.o unsort.o unittest.o

unittest: $(OBJECTS)
	$(CC) $(FLAGS) -o unittest $(OBJECTS)

bubblesort.o: bubblesort.cpp sort.h
	$(CC) $(CFLAGS) -c bubblesort.cpp

insertionsort.o: insertionsort.cpp sort.h
	$(CC) $(CFLAGS) -c insertionsort.cpp

mergesort.o: mergesort.cpp sort.h
	$(CC) $(CFLAGS) -c mergesort.cpp

selectionsort.o: selectionsort.cpp sort.h
	$(CC) $(CFLAGS) -c selectionsort.cpp

unsort.o: unsort.cpp sort.h
	$(CC) $(CFLAGS) -c unsort.cpp

unittest.o: unittest.cpp
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)

