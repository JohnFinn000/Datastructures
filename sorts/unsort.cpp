/*
 * =====================================================================================
 *
 *       Filename:  unsort.cpp
 *
 *    Description:  unsorts a bunch of things
 *
 *        Version:  1.0
 *        Created:  02/20/2013 02:53:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#define VERBOSE 1

void unsort( int arr[], int size ) {

	int array[size];

	srand(time(NULL));

	for( int i = 0; i < 10; ++i ) {
		array[i] = rand() % 100;
	}

	// mergesort the array

}

