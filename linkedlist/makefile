

GTEST_DIR = ../../gtest-1.7.0
CC = g++
CFLAGS = -g -Wall -Wextra -pthread -isystem $(GTEST_DIR)/include
OBJDIR = obj

OBJECTS = linkedlist_ut.o

all: linkedlist_ut

linkedlist_ut: gtest list.h list.hxx list_iterator.hxx
	$(CC) $(CFLAGS) unittests/linkedlist_ut.cpp libgtest.a \
					-o linkedlist_ut

gtest:
	$(CC) $(CFLAGS) -I${GTEST_DIR} \
		-c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

.PHONY: clean
clean:
	rm linkedlist_ut $(OBJECTS)

