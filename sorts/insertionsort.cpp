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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define VERBOSE 1


//allow ascending or descending
void insertion_sort( int arr[], int size ) {


	// first make sure there is enough to bother sorting
	if( size < 2 ) {
		return;
	}

	int index_lowest = 0;

	for( int i = 0; i < size; ++i ) {

#if VERBOSE >= 1
		printf("%d) ", i);
		for( int k = 0; k < 10; ++k ) {
			printf("%d ", arr[k]);
		}
		printf("\n");
#endif

		// swap the values
		for( int j = i; j > 0; --j ) {
			if( arr[j] < arr[j-1] ) {
				arr[j] ^= arr[j-1];
				arr[j-1] ^= arr[j];
				arr[j] ^= arr[j-1];
			} else {
				break;
			}
		}

	}

#if VERBOSE >= 1
		printf("%d) ", size);
		for( int k = 0; k < 10; ++k ) {
			printf("%d ", arr[k]);
		}
		printf("\n");
#endif

}









