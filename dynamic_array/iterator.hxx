/*
 * =====================================================================================
 *
 *       Filename:  iterator.hxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/20/2013 04:24:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "dynamic_array.hh"

//iterator
template<class T>
Dynamic_array<T>::iterator::iterator( ) {

    current_index = 0;
}

template<class T>
Dynamic_array<T>::iterator::iterator( Dynamic_array<T> *o ) {

    owner = o;
    current_index = 0;
}

template<class T>
Dynamic_array<T>::iterator::iterator( Dynamic_array<T> *o, int start ) {

    owner = o;
    current_index = start;
}

template<class T>
bool Dynamic_array<T>::iterator::end() {

    if( current_index >= owner->size ) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool Dynamic_array<T>::iterator::start() {

    if( current_index < 0 ) {
        return true;
    } else {
        return false;
    }
}

template<class T>
T Dynamic_array<T>::iterator::next() {

    if( current_index == owner->size ) {
        return 0;
    } else {
        ++current_index;
        return owner->data[current_index];
    }
}

template<class T>
T Dynamic_array<T>::iterator::previous() {

    if( current_index < 0 ) {
        return 0;
    } else {
        --current_index;
        return owner->data[current_index];
    }
}

template<class T>
T Dynamic_array<T>::iterator::get() {

    return owner->data[current_index];
}

//sugar
template<class T>
T Dynamic_array<T>::iterator::operator++() {
    return forward();
}

template<class T>
T Dynamic_array<T>::iterator::operator--() {
    return previous();
}

template<class T>
T Dynamic_array<T>::iterator::forward() {
    return next();
}

template<class T>
T Dynamic_array<T>::iterator::back() {
    return previous();
}

