/*
 * =====================================================================================
 *
 *       Filename:  dynamic_array.hxx
 *
 *    Description:  a generic dynamic array implementation
 *
 *        Version:  1.0
 *        Created:  03/12/2013 11:58:16 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _DYNAMIC_ARRAY_HXX__
#define _DYNAMIC_ARRAY_HXX__
#include "dynamic_array.hh"

//constructor
template<class T>
Dynamic_array<T>::Dynamic_array() {

    capacity = 1;
    size = 0;
    
    data = new T[capacity];
}

template<class T>
Dynamic_array<T>::Dynamic_array( const Dynamic_array &other ) {
    
    size = other.get_size();
    capacity = size;
    
    data = new T[capacity];

    for( int i = 0; i < size; ++i ) {
        data[i] = other[i];
    }
}

template<class T>
Dynamic_array<T>::Dynamic_array( int initial_size ) {

    capacity = initial_size;
    size = 0;

    data = new T[capacity];
}

template<class T>
Dynamic_array<T>::Dynamic_array( T arr[], int arr_size, int initial_size ) {
    
    capacity = (arr_size > initial_size ? arr_size : initial_size);
    size = arr_size;

    data = new T[capacity];
    
    for( int i = 0; i < size; ++i ) {
        data[i] = arr[i];
    }
}

template<class T>
Dynamic_array<T>::~Dynamic_array() {

    delete[] data;
}

template<class T>
void Dynamic_array<T>::add( T num ) {
    
    // resize if more space is needed
    if( size >= capacity ) {
        resize( capacity * 2 ); // resize
    }

    // size-1 is the index. Since we know the size will be
    // incremented in a second we use the current size as the index
    data[size] = num;
    ++size;
}

template<class T>
void Dynamic_array<T>::add( T arr[], int arr_size ) {
    
    // resize if more space is needed
    if( size + arr_size >= capacity ) {
        resize( capacity + arr_size ); // resize
    }

    for( int i = 0; i < arr_size; ++i ) {
        data[size + i] = arr[i];
    }
    size += arr_size;
}

template<class T>
void Dynamic_array<T>::add( Dynamic_array<T> *new_arr ) {

    // resize if more space is needed
    int arr_size = new_arr->get_size();
    if( size + arr_size >= capacity ) {
        resize( capacity + arr_size ); // resize
    }

    for( int i = 0; i < arr_size; ++i ) {
        data[size + i] = (*new_arr)[i];
    }
    size += arr_size;
}

template<class T>
void Dynamic_array<T>::insert( T num, int index ) {

    // resize if more space is needed
    if( size >= capacity ) {
        resize( capacity * 2 ); // resize
    }

    // shift elements forward
    for( int i = size; i > index; --i ) {
        data[i] = data[i-1];
    }

    data[index] = num;
    ++size;
}

template<class T>
void Dynamic_array<T>::resize( int new_size ) {

    if( new_size < capacity ) {
        if( new_size > size ) {
            capacity = new_size;
        }
        
    } else {
        T *data_array = new T[new_size];

        for( int i = 0; i < size; ++i ) {
            data_array[i] = data[i];
        }

        delete[] data;
        data = data_array;

        capacity = new_size;
    }
}

template<class T>
void Dynamic_array<T>::fit() {

    capacity = size;
    //TODO free the unused capacity
}

template<class T>
void Dynamic_array<T>::sort( ) {

    insertion_sort( data, size );
}

template<class T>
void Dynamic_array<T>::sort( bool (*compfunc)(T, T) ) {

    insertion_sort( data, size, compfunc );
}

template<class T>
T& Dynamic_array<T>::get( int index ) {

    if( index < 0 ) { // not valid (obviously)
        return NULL;
    } else if( index < size ) { // this is okay
        return data[index];
    } else { // also not valid
        return NULL;
    }

}

template<class T>
T& Dynamic_array<T>::get_now( int index ) {

    return data[index];
}

template<class T>
int Dynamic_array<T>::get_size() {

    return size;
}

template<class T>
int Dynamic_array<T>::get_capacity() {

    return capacity;
}
template<class T>
typename Dynamic_array<T>::iterator *Dynamic_array<T>::begin() {

    Dynamic_array::iterator *iter = new Dynamic_array::iterator( this );
    return iter;
}

template<class T>
typename Dynamic_array<T>::iterator *Dynamic_array<T>::end() {

    Dynamic_array::iterator *iter = new Dynamic_array::iterator( this, size-1 );
    return iter;
}


//sugar
template<class T>
T& Dynamic_array<T>::operator[]( int index ) {

    return data[index];
}

template<class T>
void Dynamic_array<T>::operator+( T num ) {

    add( num );
}

template<class T>
void Dynamic_array<T>::operator+( Dynamic_array<T> *arr ) {

    add( arr );
}

#endif



