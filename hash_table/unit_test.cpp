/*
 * =====================================================================================
 *
 *       Filename:  unit_test.cpp
 *
 *    Description:  this is a unit test for dynamic_array
 *
 *        Version:  1.0
 *        Created:  03/14/2013 06:57:59 PM
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
#include "dynamic_array.hh"

int main() {


    Dynamic_array<int> dyn_arr;

    for( int i = 0; i < 10; ++i ) {
        dyn_arr.add( (i*52353151353) % 500 );
    }

    printf("capacity: %d, size: %d\n", dyn_arr.get_capacity(), dyn_arr.get_size() );

    
    printf("getting and changing elements \n");
    int size = dyn_arr.get_size();
    for( int i = 0; i < size; ++i ) {
        dyn_arr.get_now(i) += 13252;
        printf("element %d: %d \n", i, dyn_arr.get_now(i) );
    }

    printf("array addition \n");
    int arr[5] = { 512, 24, 2 ,4, 6 };
    dyn_arr.add( arr, 5 );

    size = dyn_arr.get_size();
    for( int i = 0; i < size; ++i ) {
        printf("element %d: %d \n", i, dyn_arr.get_now(i) );
    }

    printf("iterator forward \n");
    Dynamic_array<int>::iterator *iter = dyn_arr.begin();
    for( ; !iter->end(); iter->next() ) {
        printf("%d\n", iter->get() );
    }

    printf("iterator backward \n");
    iter = dyn_arr.end();
    for( ; !iter->start(); iter->previous() ) {
        printf("%d\n", iter->get() );
    }
}




