/*
 * =====================================================================================
 *
 *       Filename:  mass.hxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/20/2013 04:22:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "dynamic_array.hh"

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

