/*
 * =====================================================================================
 *
 *       Filename:  utilities.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/14/2013 08:04:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "utilities.hh"

template <>
void print_array<int>( int arr[], int size ) { 
    if( size >= 1 ) { 
        printf("{ %d", arr[0]);
        for( int i = 1; i < size; ++i ) { 
            printf(", %d", arr[i] );
        }   
        printf(" }\n");
    } else {
        printf("{ }\n");
    }   
}

template <>
void print_array<float>( float arr[], int size ) { 
    if( size >= 1 ) { 
        printf("{ %f", arr[0]);
        for( int i = 1; i < size; ++i ) { 
            printf(", %f", arr[i] );
        }   
        printf(" }\n");
    } else {
        printf("{ }\n");
    }   
}


