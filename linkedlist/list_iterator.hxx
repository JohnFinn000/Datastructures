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

//forward_iterator
template<class T>
List<T>::forward_iterator::forward_iterator() {
    iterable = NULL;
	current = NULL;
}

template<class T> //TODO make this a working copy constructor
List<T>::forward_iterator::forward_iterator( const forward_iterator &other ) {
    iterable = NULL;
	current = NULL;
}

template<class T>
List<T>::forward_iterator::forward_iterator( List *owner, link *start ) {
    iterable = owner;
	current = start;
}

template<class T>
T* List<T>::forward_iterator::next() {
	if( current ) {
		current = current->next;
        if( current ) {
            return current->node;
        }
	}
	return 0;
}

template<class T>
T* List<T>::forward_iterator::next_() {
	T *temp = NULL;;
	if( current ) {
		temp = current->node;
		current = current->next;
	}
	return temp;
}

template<class T>
T* List<T>::forward_iterator::get() {
	if( current ) {
		return current->node;
	}
	return 0;
}

template<class T>
void List<T>::forward_iterator::insert( T& node __attribute__((unused)) ) {
}

template<class T>
T* List<T>::forward_iterator::remove() {
    return NULL;
}

template<class T>
void List<T>::forward_iterator::set( T& node __attribute__((unused)) ) {
}

template<class T>
bool List<T>::forward_iterator::end() {
    if( current ) {
        return false;
    }
    return true;
}

template<class T>
bool List<T>::forward_iterator::start() {
    if( iterable->head == current ) {
        return true;
    }
    return false;
}

//sugar
template<class T>
T *List<T>::forward_iterator::operator+( T node ) {
	if( current ) {
		return this.current->node + node;
	}
	return NULL;
}	

template<class T>
T *List<T>::forward_iterator::operator-( T node ) {
	if( current ) {
		return this.current->node - node;
	}
	return NULL;
}

template<class T>
bool List<T>::forward_iterator::operator==( T node ) {
	if( this.node == node ) {
		return true;
	}
	return false;
}

template<class T>
bool List<T>::forward_iterator::operator==( forward_iterator *iter ) {
	if( current == iter->current() ) {
		return true;
	}
	return false;
}

template<class T>
bool List<T>::forward_iterator::operator!=( forward_iterator *iter ) {
	if( current != iter->current() ) {
		return true;
	}
	return false;
}

#endif

