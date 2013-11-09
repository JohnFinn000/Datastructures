/*
 * =====================================================================================
 *
 *       Filename:  bubble_sort.hxx
 *
 *    Description:  bubble sort aka worst sort ever
 *
 *        Version:  1.0
 *        Created:  02/20/2013 02:38:48 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _BUBBLE_SORT__
#define _BUBBLE_SORT__

#include "utilities.hh"

template <typename T>
void bubble_sort( T arr[], int size, bool (*compfunc)( T, T ) ) {

	// first make sure there is enough to bother sorting
	if( size < 2 ) {
		return;
	}

	for( int i = 0; i < size; ++i ) {
		for( int j = 0; j < (size - i) - 1; ++j ) {
			// swap the values if the left value is the larger
			if( compfunc( arr[j], arr[j+1] ) ) {
                T temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
			}
		}
	}
}

template <typename T>
void bubble_sort( T arr[], int size ) {
    bubble_sort( arr, size, compare );
}

#endif

