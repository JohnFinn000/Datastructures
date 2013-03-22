/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2012 03:56:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (JF), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "list.h"


//List
template<class T>
List<T>::List() {
	head = NULL;
	tail = &head;
}

template<class T>
List<T>::~List() {

}

template<class T>
typename List<T>::link *List<T>::get_head() {
	return head;
}

template<class T>
void List<T>::add_front( T node ) {
	link *new_node = new link;
	new_node->node = new T;
	(*new_node->node) = node;
	new_node->next = head;
	head = new_node;
}


template<class T>
void List<T>::remove_front() {
	link *temp = head;
	if( head ) {
		head = head->next;
	}
	free(temp);
}

template<class T>
void List<T>::add_back( T node ) {
	link *new_node = new link;
	new_node->node = node;
	new_node->next = NULL;

	(*tail) = new_node;
	tail = &((*tail)->next);
	
}

template<class T>
void List<T>::splice( List *splicee ) {
	tail = &splicee->get_head();
}



template<class T>
typename List<T>::iterator *List<T>::begin() {
	List::iterator *iter = new List::iterator( head );
	return iter;
}

template<class T>
typename List<T>::iterator *List<T>::end() {
	List::iterator *iter = new List::iterator( *tail );
	return iter;
}


//sugar
template<class T>
void List<T>::operator+( T node ) {
	add_front( node );
}

template<class T>
void List<T>::operator+( List l ) {
	splice( l );
}

template<class T>
void List<T>::operator--() {
	remove_front();
}


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


















