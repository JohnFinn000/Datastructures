/*
 * =====================================================================================
 *
 *       Filename:  utilities.hh
 *
 *    Description:  utilities header
 *
 *        Version:  1.0
 *        Created:  04/13/2013 12:54:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _UTILITIES_HH__
#define _UTILITIES_HH__
#include <stdio.h>

template <typename T>
bool compare( T a, T b );

template <typename T>
void print_array( T arr[], int size );

template <>
void print_array( int arr[], int size );

template <>
void print_array( float arr[], int size );


#include "utilities.hxx"
#endif

