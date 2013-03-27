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
#include "sort.h"

void selection_sort( int arr[], int size ) {

    selection_sort( arr, size, compare );
}

void selection_sort( int arr[], int size, bool (*compfunc)(int, int) ) {


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
			if( compfunc( arr[index_lowest], arr[j] ) ) {
				index_lowest = j;
			}
		}

		// swap the values
		if( i != index_lowest ) {
            SWAP( arr[i], arr[index_lowest] );
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

