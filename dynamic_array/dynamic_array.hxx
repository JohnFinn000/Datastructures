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
#include <stdlib.h>
#include <math.h>
#include "dynamic_array.hh"

//constructor
template<class T>
Dynamic_array<T>::Dynamic_array() {

    capacity = 1;
    size = 0;
    
    data = new T[capacity];
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

//destructor
template<class T>
Dynamic_array<T>::~Dynamic_array() {

    //delete data [capacity];
}

template<class T>
void Dynamic_array<T>::add( T num ) {
    
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
    
    if( size + arr_size >= capacity ) {
        resize( capacity + arr_size ); // resize
    }

    for( int i = 0; i < arr_size; ++i ) {
        data[size + i] = arr[i];
    }
    size += arr_size;
    
}

template<class T>
void Dynamic_array<T>::insert( T num, int index ) {
    // shift elements forward


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
void Dynamic_array<T>::resize( int new_size ) {

    if( new_size < capacity ) {
        
    } else {
        T *data_array = new T[new_size];

        for( int i = 0; i < size; ++i ) {
            data_array[i] = data[i];
        }

        data = data_array;

        capacity = new_size;
    }
}

template<class T>
void Dynamic_array<T>::fit() {

    //capacity = size;
    //free the unused capacity


}

template<class T>
void Dynamic_array<T>::sort( ) { // needs comparison function

}

template<class T>
typename Dynamic_array<T>::iterator *Dynamic_array<T>::begin() {

    Dynamic_array::iterator *iter = new Dynamic_array::iterator( this );
    return iter;
}

template<class T>
typename Dynamic_array<T>::iterator *Dynamic_array<T>::end() {

    Dynamic_array::iterator *iter = new Dynamic_array::iterator( this, size );
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

//mass
template<class T>
Dynamic_array<T>::mass::mass( ) {
}

template<class T>
Dynamic_array<T>::mass::mass( Dynamic_array<T> *o ) {
    owner = o;
    num_indices = owner->size;
    indices = (int*) malloc( sizeof(int) *num_indices );
    for( int i = 0; i < num_indices; ++i ) {
        indices[i] = i;
    }
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::equal( T param ) {
    int i, k;
    for( i = 0, k = 0; k < num_indices && indices[k] >= 0; ++k ) {
        if( !(owner->data[indices[k]] == param) ) {
            indices[k] = -1;
        } else {
            indices[i] = indices[k];
            if( i != k ) { 
                indices[k] = -1;
            }
            ++i;
        }
    }
    size = i;
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::not_equal( T param ) {
    int i, k;
    for( i = 0, k = 0; k < num_indices && indices[k] >= 0; ++k ) {
        if( !(owner->data[indices[k]] != param) ) {
            indices[k] = -1;
        } else {
            indices[i] = indices[k];
            if( i != k ) { 
                indices[k] = -1;
            }
            ++i;
        }
    }
    size = i;
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::greater( T param ) {
    int i, k;
    for( i = 0, k = 0; k < num_indices && indices[k] >= 0; ++k ) {
        if( !(owner->data[indices[k]] > param) ) {
            indices[k] = -1;
        } else {
            indices[i] = indices[k];
            if( i != k ) { 
                indices[k] = -1;
            }
            ++i;
        }
    }
    size = i;
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::greater_equal( T param ) {
    int i, k;
    for( i = 0, k = 0; k < num_indices && indices[k] >= 0; ++k ) {
        if( !(owner->data[indices[k]] >= param) ) {
            indices[k] = -1;
        } else {
            indices[i] = indices[k];
            if( i != k ) { 
                indices[k] = -1;
            }
            ++i;
        }
    }
    size = i;
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::less( T param ) {
    int i, k;
    for( i = 0, k = 0; k < num_indices && indices[k] >= 0; ++k ) {
        if( !(owner->data[indices[k]] < param) ) {
            indices[k] = -1;
        } else {
            indices[i] = indices[k];
            if( i != k ) { 
                indices[k] = -1;
            }
            ++i;
        }
    }
    size = i;
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::less_equal( T param ) {
    int i, k;
    for( i = 0, k = 0; k < num_indices && indices[k] >= 0; ++k ) {
        if( !(owner->data[indices[k]] <= param) ) {
            indices[k] = -1;
        } else {
            indices[i] = indices[k];
            if( i != k ) { 
                indices[k] = -1;
            }
            ++i;
        }
    }
    size = i;
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::between( T param1, T param2 ) {
    int i, k;
    for( i = 0; k < num_indices && indices[k] >= 0; ++k ) {
        if( !(owner->data[indices[k]] > param1 && owner->data[indices[k]] < param2) ) {
            indices[k] = -1;
        } else {
            indices[i] = indices[k];
            if( i != k ) { 
                indices[k] = -1;
            }
            ++i;
        }
    }
    size = i;
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::add( T param ) {
    for( int i = 0; i < num_indices && indices[i] >= 0; ++i ) {
        owner->data[indices[i]] += param;
    }
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::subtract( T param ) {
    for( int i = 0; i < num_indices && indices[i] >= 0; ++i ) {
        owner->data[indices[i]] -= param;
    }
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::multiply( T param ) {
    for( int i = 0; i < num_indices && indices[i] >= 0; ++i ) {
        owner->data[indices[i]] *= param;
    }
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::divide( T param ) {
    for( int i = 0; i < num_indices && indices[i] >= 0; ++i ) {
        owner->data[indices[i]] /= param;
    }
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::modulo( T param ) {
    for( int i = 0; i < num_indices && indices[i] >= 0; ++i ) {
        owner->data[indices[i]] %= param;
    }
    return *this;
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::pow( int param ) {
    for( int i = 0; i < num_indices && indices[i] >= 0; ++i ) {
        T temp = owner->data[indices[i]];
        owner->data[indices[i]] = 1;
        for( int k = 0; k < param; ++k ) {
            owner->data[indices[i]] *= temp;
        }
    }
    return *this;
}

//sort
template<class T>
void Dynamic_array<T>::mass::sort_ascending() {


}

template<class T>
void Dynamic_array<T>::mass::sort_descending() {


}

template<class T>
T *Dynamic_array<T>::mass::get( int &size ) {
    for( size = 0; size < num_indices && indices[size] >= 0; ++size );

    T *ret = new T[size]; 
    
    for( int i = 0; i < size; ++i ) {
        ret[i] = owner->data[indices[i]];
    }

    return ret;

}

template<class T>
int Dynamic_array<T>::mass::get_size( ) {
    return size;
}

//sugar
//logic operators
template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator==( T param ) {
    return equal( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator!=( T param ) {
    return not_equal( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator>( T param ) {
    return greater( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator>=( T param ) {
    return greater_equal( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator<( T param ) {
    return less( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator<=( T param ) {
    return less_equal( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator()( T param1, T param2 ) {
    return between( param1, param2 );
}

//arithmetic operators
template<class T>
T Dynamic_array<T>::mass::operator+=( T param ) {
    add( param );
    return param;
}

template<class T>
T Dynamic_array<T>::mass::operator-=( T param ) {
    subtract( param );
    return param;
}

template<class T>
T Dynamic_array<T>::mass::operator*=( T param ) {
    multiply( param );
    return param;
}

template<class T>
T Dynamic_array<T>::mass::operator/=( T param ) {
    divide( param );
    return param;
}

template<class T>
T Dynamic_array<T>::mass::operator%=( T param ) {
    modulo( param );
    return param;
}


template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator+( T param ) {
    return add( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator-( T param ) {
    return subtract( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator*( T param ) {
    return multiply( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator/( T param ) {
    return divide( param );
}

template<class T>
typename Dynamic_array<T>::mass &Dynamic_array<T>::mass::operator%( T param ) {
    return modulo( param );
}

template<class T>
bool Dynamic_array<T>::mass::operator!( ) {
    if( get_size() > 0 ) {
        return false;
    } else {
        return true;
    }
}
#endif



