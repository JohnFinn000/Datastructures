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
#ifndef _ITERATOR_HXX__
#define _ITERATOR_HXX__
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
T* Dynamic_array<T>::iterator::next() {

    if( current_index == owner->size ) {
        return 0;
    } else {
        ++current_index;
        return &owner->data[current_index];
    }
}

template<class T>
T* Dynamic_array<T>::iterator::next_() {

    if( current_index == owner->size ) {
        return 0;
    } else {
        ++current_index;
        return &owner->data[current_index-1];
    }
}

template<class T>
T* Dynamic_array<T>::iterator::previous() {

    if( current_index < 0 ) {
        return 0;
    } else {
        --current_index;
        return &owner->data[current_index];
    }
}

template<class T>
T* Dynamic_array<T>::iterator::previous_() {

    if( current_index < 0 ) {
        return 0;
    } else {
        --current_index;
        return &owner->data[current_index+1];
    }
}

template<class T>
T* Dynamic_array<T>::iterator::get() {

    return &owner->data[current_index];
}


template<class T>
void Dynamic_array<T>::iterator::insert( T val ) {

    //TODO insert
}


template<class T>
T* Dynamic_array<T>::iterator::remove() {

    return &owner->data[current_index];
}


template<class T>
void Dynamic_array<T>::iterator::set( T val ) {
    
}

#endif
