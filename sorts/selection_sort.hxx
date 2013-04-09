/*
 * =====================================================================================
 *
 *       Filename:  selection_sort.hxx
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
#ifndef _SELECTION_SORT_HXX__
#define _SELECTION_SORT_HXX__

#include "utilities.hxx"

template <typename T>
void selection_sort( T arr[], int size ) {

    selection_sort( arr, size, compare );
}

template <typename T>
void selection_sort( T arr[], int size, bool (*compfunc)(T, T) ) {

	// first make sure there is enough to bother sorting
	if( size < 2 ) {
		return;
	}

	int index_lowest = 0;

	for( int i = 0; i < size; ++i ) {

		for( int j = index_lowest = i; j < size; ++j ) {
			if( compfunc( arr[index_lowest], arr[j] ) ) {
				index_lowest = j;
			}
		}

		// swap the values
		if( i != index_lowest ) {
            T temp = arr[i];
            arr[i] = arr[index_lowest];
            arr[index_lowest] = temp;
		}

	}

}

#endif
