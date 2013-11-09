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
#include "dynamic_array.hxx"

int main() {


    Dynamic_array<int> dyn_arr;

    for( int i = 0; i < 5; ++i ) {
        dyn_arr.add( (i*52353151353) % 500 );
    }

    printf("capacity: %d, size: %d\n", dyn_arr.get_capacity(), dyn_arr.get_size() );

    printf("getting and changing elements \n");
    int size = dyn_arr.get_size();
    for( int i = 0; i < size; ++i ) {
        dyn_arr.get_now(i) += 13252;
        printf("%d, ", dyn_arr.get_now(i) );
    }
    printf("\n");

    printf("array addition \n");
    int arr[5] = { 512, 24, 2 ,4, 6 };
    dyn_arr.add( arr, 5 );

    size = dyn_arr.get_size();
    for( int i = 0; i < size; ++i ) {
        printf("%d, ", dyn_arr.get_now(i) );
    }
    printf("\n");

    printf("dynamic array addition \n");
    Dynamic_array<int> new_arr;
    for( int i = 100; i < 110; ++i ) {
        new_arr.add( i );
    }
    dyn_arr.add( &new_arr );
    size = dyn_arr.get_size();
    for( int i = 0; i < size; ++i ) {
        printf("%d, ", dyn_arr.get_now(i) );
    }
    printf("\n");

    printf("sort\n");
    dyn_arr.sort();
    size = dyn_arr.get_size();
    for( int i = 0; i < size; ++i ) {
        printf("%d, ", dyn_arr.get_now(i) );
    }
    printf("\n");

    // Iterator tests
    Dynamic_array<int>::iterator *iter;

    printf("iterator forward \n");
    for( iter = dyn_arr.begin(); !iter->end(); iter->next() ) {
        printf("%d, ", iter->get() );
    }
    printf("\n");

    printf("iterator backward \n");
    for( iter = dyn_arr.end(); !iter->start(); iter->previous() ) {
        printf("%d, ", iter->get() );
    }
    printf("\n");
/*
    Dynamic_array<int>::mass m( &dyn_arr );
    
    printf("iterator forward \n");
    iter = dyn_arr.begin();
    for( ; !iter->end(); iter->next() ) {
        printf("%d\n", iter->get() );
    }

    m.add( 25 );

    printf("iterator forward \n");
    iter = dyn_arr.begin();
    for( ; !iter->end(); iter->next() ) {
        printf("%d\n", iter->get() );
    }

    int s;
    int *a = m.get( s );
    m %= 5;
    m.pow(1);

    for( int i = 0; i < s; ++i ) {
        printf("%d, ", a[i] );
    }

    printf("iterator forward \n");
    iter = dyn_arr.begin();
    for( ; !iter->end(); iter->next() ) {
        printf("%d\n", iter->get() );
    }
*/
}




