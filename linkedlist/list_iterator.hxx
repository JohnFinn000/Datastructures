/*
 * =====================================================================================
 *
 *       Filename:  list_iterator.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/26/2013 04:03:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _LIST_ITERATOR_HXX__
#define _LIST_ITERATOR_HXX__

#include "list.h"

//iterator
template<class T>
List<T>::iterator::iterator() {
	current = NULL;
}

template<class T>
List<T>::iterator::iterator( link *start ) {
	current = start;
}

template<class T>
T List<T>::iterator::next() {
	if( current ) {
		current = current->next;
        if( current ) {
            return *current->node;
        }
	}
	return 0;
}

template<class T>
T List<T>::iterator::get() {
	if( current ) {
		return *current->node;
	}
	return 0;
}

template<class T>
void List<T>::iterator::insert( T *node ) {
}

template<class T>
void List<T>::iterator::set( T *node ) {
}

template<class T>
bool List<T>::iterator::end() {
    if( current ) {
        return false;
    }
    return true;
}

template<class T>
bool List<T>::iterator::start() {
    if( head == current ) {
        return true;
    }
    return false;
}

//sugar
template<class T>
T *List<T>::iterator::operator+( T node ) {
	if( current ) {
		return this.current->node + node;
	}
	return NULL;
}	

template<class T>
T *List<T>::iterator::operator-( T node ) {
	if( current ) {
		return this.current->node - node;
	}
	return NULL;
}

template<class T>
T *List<T>::iterator::operator++() {
	if( current ) {
		current = current->next;
		return current->node;
	}
	return NULL;
}

template<class T>
T *List<T>::iterator::operator++(int) {
	T *temp = NULL;;
	if( current ) {
		temp = current->node;
		current = current->next;
	}
	return temp;
}

template<class T>
bool List<T>::iterator::operator==( T node ) {
	if( this.node == node ) {
		return true;
	}
	return false;
}

template<class T>
bool List<T>::iterator::operator==( iterator *iter ) {
	if( current == iter->current() ) {
		return true;
	}
	return false;
}

template<class T>
bool List<T>::iterator::operator!=( iterator *iter ) {
	if( current != iter->current() ) {
		return true;
	}
	return false;
}



#endif
