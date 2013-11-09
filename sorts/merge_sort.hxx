/*
 * =====================================================================================
 *
 *       Filename:  merge_sort.hxx
 *
 *    Description:  merge sort
 *
 *        Version:  1.0
 *        Created:  02/20/2013 09:22:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _MERGE_SORT_HXX__
#define _MERGE_SORT_HXX__

#include "utilities.hxx"

// This doesn't quite work yet. The compfunc needs to be stored differently
// it prolly needs to be in a class so the template works right.

template <typename T>
T *split( T arr[], int size );
template <typename T>
T *combine( T arr_A[], int size_A, T arr_B[], int size_B );

bool (*compfunc)(int, int);

template <typename T>
void merge_sort( T arr[], int size, bool (*comparison_function)( T, T ) ) {

    compfunc = comparison_function;
    int *new_arr = split( arr, size );

    for( int i = 0; i < size; ++i ) {
        arr[i] = new_arr[i];
    }
}

template <typename T>
void merge_sort( T arr[], int size ) {

    merge_sort( arr, size, compare );
}


template <typename T>
T *split( T arr[], int size ) {

    switch( size ) {
    case 1:
        return arr;
    case 2:
        if( compfunc( arr[0], arr[1] ) ) {
            T temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
        }
        return arr;
    default:
        T *arr_A = split( arr, size/2 );
        T *arr_B = split( arr+(size/2), (size+1)/2 );
        T *new_arr = combine( arr_A, size/2, arr_B, (size+1)/2 );
        return new_arr;
        break;
    }


}

template <typename T>
T *combine( T arr_A[], int size_A, T arr_B[], int size_B ) {

    int new_size = size_A + size_B;
    int *new_arr = (int*) malloc( sizeof( int ) * new_size );

    int a = 0;
    int b = 0;
    for( int i = 0; i < new_size; ++i ) {
        if( compfunc( arr_B[b], arr_A[a] ) ) {
            new_arr[i] = arr_A[a];
            ++a;

            if( a == size_A ) { // if we've got everything from a don't do more
                                // comparisons and just fill all of b in
                for( int k = i+1; b < size_B; k++, b++ ) {
                    new_arr[k] = arr_B[b];
                }
                break;
            }
        } else {
            new_arr[i] = arr_B[b];
            ++b;

            if( b == size_B ) { // if we've got everything from b don't do more
                                // comparisons and just fill all of a in
                for( int k = i+1; a < size_A; k++, a++ ) {
                    new_arr[k] = arr_A[a];
                }
                break;
            }
        }
    }

    return new_arr;
}

#endif

