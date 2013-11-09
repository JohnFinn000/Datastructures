
OBJDIR = obj
GTEST_DIR = ../gtest-1.7.0
CC = g++
CPPFLAGS += -isystem $(GTEST_DIR)/include
CFLAGS = -g -Wall -Wextra -pthread

OBJECTS = linkedlist_ut

all: sort_ut

#sort_ut: gtest
#	$(CC) $(FLAGS) -isystem ${GTEST_DIR}/include -pthread sorts/unittests/sort_ut.cpp libgtest.a \
#				   -o sort_ut

gtest:
	g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
		-pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

clean:

