/*
 * =====================================================================================
 *
 *       Filename:  mergesort.cpp
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
#include "sort.h"

int *split( int arr[], int size );
int *combine( int arr_A[], int size_A, int arr_B[], int size_B );

bool (*compfunc)(int,int);

void merge_sort( int arr[], int size ) {

    merge_sort( arr, size, compare );
}

void merge_sort( int arr[], int size, bool (*comparison_function)(int,int) ) {

    compfunc = comparison_function;
    int *new_arr = split( arr, size );

    for( int i = 0; i < size; ++i ) {
        arr[i] = new_arr[i];
    }
}

int *split( int arr[], int size ) {

    switch( size ) {
    case 1:
        return arr;
    case 2:
        if( compfunc( arr[0], arr[1] ) ) {
            SWAP( arr[0], arr[1] );
        }
        return arr;
    default:
        int *arr_A = split( arr, size/2 );
        int *arr_B = split( arr+(size/2), (size+1)/2 );
        int *new_arr = combine( arr_A, size/2, arr_B, (size+1)/2 );
        return new_arr;
        break;
    }


}

int *combine( int arr_A[], int size_A, int arr_B[], int size_B ) {
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


