/*
 * =====================================================================================
 *
 *       Filename:  unsort.hxx
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
#ifndef _UNSORT_HXX__
#define _UNSORT_HXX__

#include <stdint.h>
#include <time.h>
#include "sort.h"
#include "selection_sort.hxx"

struct bundle {
    uint64_t number;
    int data;
};

bool compare_bundle( bundle a, bundle b );
uint64_t LCG( uint64_t seed );

template <typename T>
void unsort( T arr[], int size ) {
    static uint64_t seed = time( NULL );

    bundle new_arr[size];
    T temp_arr[size];


    for( int i = 0; i < size; ++i ) {
        seed = new_arr[i].number = LCG( seed );
        new_arr[i].data   = i;
        temp_arr[i]       = arr[i];
    }

    bubble_sort( new_arr, size, compare_bundle );
    //TODO: change this to merge sort once it's been templatized

    for( int i = 0; i < size; ++i ) {
        arr[i] = temp_arr[new_arr[i].data];
    }
}

bool compare_bundle( bundle a, bundle b ) {
    return a.number < b.number;
}

uint64_t LCG( uint64_t seed ) {

    const uint64_t MUL = 6364136223846793005;
    const uint64_t INC = 1442695040888963407;

    uint64_t x = seed;
    x = (MUL * x + INC);
    return x;

}

#endif
