/*
 * =====================================================================================
 *
 *       Filename:  generic.hxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/20/2013 01:56:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _GENERIC_HXX__
#define _GENERIC_HXX__
#include "generic.h"

template<class T>
void generic<T>::operator+( T num ) {

    add( num );
}



template<class T>
void sortable<T>::operator+() {

    sort_ascending();
}

template<class T>
void sortable<T>::operator-() {

    sort_descending();
}



template<class T>
void iterable<T>::iterator::operator+( T val ) {
    insert( val );
}

template<class T>
T iterable<T>::iterator::operator-( ) {
    remove();
}

template<class T>
void iterable<T>::iterator::operator=( T val ) {
    set( val );
}

template<class T>
T iterable<T>::reverse_iterator::operator--() {
    return previous();
}

template<class T>
T iterable<T>::reverse_iterator::operator--( int ) {
    return previous_();
}

template<class T>
T iterable<T>::forward_iterator::operator++() {
    return next();
}

template<class T>
T iterable<T>::forward_iterator::operator++( int ) {
    return next_();
}

template<class T>
T iterable<T>::reverse_iterator::back() {
    return previous();
}

template<class T>
T iterable<T>::forward_iterator::forward() {
    return next();
}

#endif

