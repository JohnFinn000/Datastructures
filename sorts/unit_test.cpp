/*
 * =====================================================================================
 *
 *       Filename:  unit_test.cpp
 *
 *    Description:  This is used to verify the correctness of the sort algorithms
 *
 *        Version:  1.0
 *        Created:  03/12/2013 12:41:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "sort.h"
#include <time.h>

int main() {

    int test_array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    printf("%-*s", 20, "initial" );
    print_array( test_array, 12 );
    clock_t t = clock();

    printf("%-*s", 20, "unsort" );
    for( int i = 0; i < 1000000; ++i ) {
        unsort( test_array, 12 );
    }
    print_array( test_array, 12 );
    printf("%ld\n", clock() - t );

    t = clock();
    printf("%-*s", 20, "bubble_sort");
    for( int i = 0; i < 1000000; ++i ) {
        unsort( test_array, 12 );
        bubble_sort( test_array, 12 );
    }
    print_array( test_array, 12 );
    printf("%ld\n", clock() - t );

    t = clock();
    printf("%-*s", 20, "insertion_sort");
    for( int i = 0; i < 1000000; ++i ) {
        unsort( test_array, 12 );
        insertion_sort( test_array, 12 );
    }
    print_array( test_array, 12 );
    printf("%ld\n", clock() - t );
    t = clock();

    printf("%-*s", 20, "selection_sort");
    for( int i = 0; i < 1000000; ++i ) {
        unsort( test_array, 12 );
        selection_sort( test_array, 12 );
    }
    print_array( test_array, 12 );
    printf("%ld\n", clock() - t );
    t = clock();


    //printf("merge_sort");
    //unsort( test_array, 12 );
    //merge_sort( test_array, 12 );
    //print_array( test_array, 12 );


}







