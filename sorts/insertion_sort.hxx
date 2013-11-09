/*
 * =====================================================================================
 *
 *       Filename:  insertionsort.cpp
 *
 *    Description:  insertion sort
 *
 *        Version:  1.0
 *        Created:  02/20/2013 03:27:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _INSERTION_SORT__
#define _INSERTION_SORT__

#include "utilities.hh"

template <typename T>
void insertion_sort( T arr[], int size, bool (*compfunc)(T, T) ) {

	// first make sure there is enough to bother sorting
	if( size < 2 ) {
		return;
	}

	for( int i = 0; i < size; ++i ) {

		// swap the values
		for( int j = i; j > 0; --j ) {
			if( compfunc( arr[j-1], arr[j] ) ) {
                T temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
			} else {
				break;
			}
		}
	}
}

template <typename T>
void insertion_sort( T arr[], int size ) {

    insertion_sort( arr, size, compare );
}

#endif
