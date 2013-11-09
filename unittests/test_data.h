/*
 * =====================================================================================
 *
 *       Filename:  linkedlist_ut.cpp
 *
 *    Description:  unit testing for the linked list class
 *
 *        Version:  1.0
 *        Created:  10/19/2013 03:26:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "gtest/gtest.h"

//ascending
//descending
//max_ascending
//max_descending
//random1
//random2
//random3
//empty

char ascending_char[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
char descending_char[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
char random_char[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

int ascending_int[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int descending_int[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
int random_int[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

unsigned int ascending_uint[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
unsigned int descending_uint[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
unsigned int random_uint[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

long ascending_long[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
long descending_long[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
long random_long[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

float ascending_float[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
float descending_float[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
float random_float[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

double ascending_double[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
double descending_double[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
double random_double[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

class test_data {
public:
    test_data() { }
    ~test_data() { }

    static void get_ascending_data( int **data );
    static void get_ascending_data( unsigned int **data );
    static void get_ascending_data( char **data );
    static void get_ascending_data( long **data );
    static void get_ascending_data( float **data );
    static void get_ascending_data( double **data );

    static void get_descending_data( int **data );
    static void get_descending_data( unsigned int **data );
    static void get_descending_data( char **data );
    static void get_descending_data( long **data );
    static void get_descending_data( float **data );
    static void get_descending_data( double **data );

    static void get_random_data( int **data );
    static void get_random_data( unsigned int **data );
    static void get_random_data( char **data );
    static void get_random_data( long **data );
    static void get_random_data( float **data );
    static void get_random_data( double **data );
};

// ascending data
void test_data::get_ascending_data( int **data ) { *data = ascending_int; }

void test_data::get_ascending_data( unsigned int **data ) { *data = ascending_uint; }

void test_data::get_ascending_data( char **data ) { *data = ascending_char; }

void test_data::get_ascending_data( long **data ) { *data = ascending_long; }

void test_data::get_ascending_data( float **data ) { *data = ascending_float; }

void test_data::get_ascending_data( double **data ) { *data = ascending_double; }

// descending data
void test_data::get_descending_data( int **data ) { *data = descending_int; }

void test_data::get_descending_data( unsigned int **data ) { *data = descending_uint; }

void test_data::get_descending_data( char **data ) { *data = descending_char; }

void test_data::get_descending_data( long **data ) { *data = descending_long; }

void test_data::get_descending_data( float **data ) { *data = descending_float; }

void test_data::get_descending_data( double **data ) { *data = descending_double; }

// random data
void test_data::get_random_data( int **data ) { *data = random_int; }

void test_data::get_random_data( unsigned int **data ) { *data = random_uint; }

void test_data::get_random_data( char **data ) { *data = random_char; }

void test_data::get_random_data( long **data ) { *data = random_long; }

void test_data::get_random_data( float **data ) { *data = random_float; }

void test_data::get_random_data( double **data ) { *data = random_double; }
