
OBJDIR = obj
GTEST_DIR = ../../../gtest-1.7.0
CC = g++
CPPFLAGS += -isystem $(GTEST_DIR)/include
CFLAGS = -g -Wall -Wextra -pthread

OBJECTS = sort_ut

all: sort_ut

sort_ut: gtest sort_ut.cpp ../bubble_sort.hxx ../insertion_sort.hxx ../selection_sort.hxx ../merge_sort.hxx ../unsort.hxx ../sort.h
	$(CC) $(FLAGS) -isystem ${GTEST_DIR}/include -pthread sort_ut.cpp libgtest.a \
				   -o sort_ut

gtest:
	g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
		-pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

clean:

