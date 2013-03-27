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

void print_array( int arr[], int size ) {

    if( size >= 1 ) {
        printf("{ %d", arr[0]);
        for( int i = 1; i < size; ++i ) {
            printf(", %d", arr[i] );
        }
        printf(" }\n");
    }

}

bool descending_compare( int a, int b ) {
    return a > b;
}

int main() {

    int test_array[] = { 6, 4, 2, 3, 1, 7, 7, 8, 2, 2, 2, 4 };

    print_array( test_array, 12 );

    //bubble_sort( test_array, 12, descending_compare );
    //insertion_sort( test_array, 12 );
    //selection_sort( test_array, 12 );
    merge_sort( test_array, 12 );

    print_array( test_array, 12 );


}







