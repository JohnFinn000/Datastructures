/*
 * =====================================================================================
 *
 *       Filename:  selectionsort.cpp
 *
 *    Description:  selection sort
 *
 *        Version:  1.0
 *        Created:  02/20/2013 03:16:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define VERBOSE 0

void selection_sort( int arr[], int size ) {


	// first make sure there is enough to bother sorting
	if( size < 2 ) {
		return;
	}

	int index_lowest = 0;

	for( int i = 0; i < size; ++i ) {

#if VERBOSE >= 1
		printf("%d) ", i);
		for( int k = 0; k < size; ++k ) {
			printf("%d ", arr[k]);
		}
		printf("\n");
#endif

		for( int j = index_lowest = i; j < size; ++j ) {
			if( arr[index_lowest] > arr[j] ) {
				index_lowest = j;
			}
		}

		// swap the values
		if( i != index_lowest ) {
			arr[i] ^= arr[index_lowest];
			arr[index_lowest] ^= arr[i];
			arr[i] ^= arr[index_lowest];
		}

	}

#if VERBOSE >= 1
		printf("%d) ", size);
		for( int k = 0; k < size; ++k ) {
			printf("%d ", arr[k]);
		}
		printf("\n");
#endif

}

