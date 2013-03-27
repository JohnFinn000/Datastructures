
CC = g++
CFLAGS = -g -Wall
OBJDIR = obj

OBJECTS = bubblesort.o insertionsort.o mergesort.o selectionsort.o unsort.o unit_test.o

unit_test: $(OBJECTS)
	$(CC) $(FLAGS) -o unit_test $(OBJECTS)

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

unit_test.o: unit_test.cpp
	$(CC) $(CFLAGS) -c unit_test.cpp

clean:
	rm unit_test $(OBJECTS)

