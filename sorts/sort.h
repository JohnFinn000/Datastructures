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

#define VERBOSE 0

template <typename T>
void print_array( T arr[], int size );

template <typename T>
bool compare( T a, T b );

template <typename T>
void bubble_sort( T arr[], int size );
template <typename T>
void bubble_sort( T arr[], int size, bool (*compfunc)( T, T ) );

template <typename T>
void insertion_sort( T arr[], int size );
template <typename T>
void insertion_sort( T arr[], int size, bool (*compfunc)(T, T) );

template <typename T>
void selection_sort( T arr[], int size );
template <typename T>
void selection_sort( T arr[], int size, bool (*compfunc)(T, T) );

template <typename T>
void merge_sort( T arr[], int size );
template <typename T>
void merge_sort( T arr[], int size, bool (*compfunc)(T, T) );

void LSB_radix_sort( int arr[], int length );

template <typename T>
void unsort( T arr[], int size );

#include "utilities.hh"
#include "bubble_sort.hxx"
#include "selection_sort.hxx"
#include "insertion_sort.hxx"
#include "merge_sort.hxx"
#include "unsort.hxx"
#endif

