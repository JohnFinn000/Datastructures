

GTEST_DIR = ../../gtest-1.7.0
CC = g++
CFLAGS = -g -Wall -Wextra -pthread -isystem $(GTEST_DIR)/include
OBJDIR = obj

OBJECTS = dynamic_array_ut.o

all: dynamic_array_ut

dynamic_array_ut: gtest dynamic_array_ut.cpp dynamic_array.hh dynamic_array.hxx iterator.hxx mass.hxx
	$(CC) $(CFLAGS) dynamic_array_ut.cpp libgtest.a \
					-o dynamic_array_ut

gtest:
	$(CC) $(CFLAGS) -I${GTEST_DIR} \
		-c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

.PHONY: clean
clean:
	rm dynamic_array_ut $(OBJECTS)

