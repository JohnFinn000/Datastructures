/*
 * =====================================================================================
 *
 *       Filename:  sort.h
 *
 *    Description:  A variety of sort functions
 *
 *        Version:  1.0
 *        Created:  03/12/2013 12:41:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _SORT_H__ // inclusion gaurd
#define _SORT_H__

#include <stdlib.h>
#include <stdio.h>

#define SWAP( a, b ) \
a ^= b;\
b ^= a;\
a ^= b;

#define VERBOSE 0

void print_array( int arr[], int size );
bool compare( int a, int b );


void bubble_sort( int arr[], int size );
void bubble_sort( int arr[], int size, bool (*compfunc)(int, int) );

void insertion_sort( int arr[], int size );
void insertion_sort( int arr[], int size, bool (*compfunc)(int, int) );

void selection_sort( int arr[], int size );
void selection_sort( int arr[], int size, bool (*compfunc)(int, int) );

void merge_sort( int arr[], int size );
void merge_sort( int arr[], int size, bool (*compfunc)(int, int) );

void unsort( int arr[], int size );

#endif
