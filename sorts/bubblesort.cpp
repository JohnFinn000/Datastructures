/*
 * =====================================================================================
 *
 *       Filename:  bubblesort.cpp
 *
 *    Description:  bubble sort aka worst sort ever
 *                  with the verbose flag on it will describe
 *                  everything it is doing
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
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sort.h"

#define VERBOSE 1

void bubble_sort( int arr[], int size ) {

	// first make sure there is enough to bother sorting
	if( size < 2 ) {
		return;
	}

	for( int i = 0; i < size; ++i ) {

#if VERBOSE >= 1
		printf("%d) ", i);
		for( int k = 0; k < 10; ++k ) {
			printf("%d ", arr[k]);
		}
		printf("\n");
#endif

		for( int j = 0; j < (size - i) - 1; ++j ) {

#if VERBOSE >= 2
			printf("%d|%d) ", i, j);
			for( int k = 0; k < 10; ++k ) {
				printf("%d ", arr[k]);
			}
			printf("\n");
#endif

			// swap the values if the left value is the larger
			if( arr[j] > arr[j+1] ) {
				arr[j] ^= arr[j+1];
				arr[j+1] ^= arr[j];
				arr[j] ^= arr[j+1];
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

/*
void bubble_sort( int arr[], int size ) {

	// first make sure there is enough to bother sorting
	if( size < 2 ) {
		return;
	}

	for( int i = 0; i < size; ++i ) {
		for( int j = 0; j < (size - i) - 1; ++j ) {
			// swap the values if the left value is the larger
			if( compare( arr[j],  arr[j+1] ) ) {
				arr[j] ^= arr[j+1];
				arr[j+1] ^= arr[j];
				arr[j] ^= arr[j+1];
			}
		}
	}
}
*/
